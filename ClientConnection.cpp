//  Copyright (C) 1997, 1998 Olivetti & Oracle Research Laboratory
//
//  This file is part of the VNC system.
//
//  The VNC system is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
//  USA.
//
// If the source code for the VNC system is not available from the place 
// whence you received this file, check http://www.orl.co.uk/vnc or contact
// the authors on vnc@orl.co.uk for information on obtaining it.


// This is the main source for a ClientConnection object.
// It handles almost everything to do with a connection to a server.
// The decoding of specific rectangle encodings is done in separate files.

#include "stdhdrs.h"

#include "vncviewer.h"

#include "omnithreadce.h"
#define SD_BOTH 0x02

#include "ClientConnection.h"
#include "SessionDialog.h"
#include "AuthDialog.h"
#include "AboutBox.h"

#include "Exception.h"
extern "C" {
	#include "vncauth.h"
}

#define INITIALNETBUFSIZE 4096
#define MAX_ENCODINGS 10
#define VWR_WND_CLASS_NAME _T("VNCviewer")

const rfbPixelFormat vnc8bitFormat = {8, 8, 1, 1, 7,7,3, 0,3,6,0,0};
const rfbPixelFormat vnc16bitFormat = {16, 16, 1, 1, 63, 31, 31, 0,6,11,0,0};

static LRESULT CALLBACK ClientConnection::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// Some handy classes for temporary GDI object selection
// These select objects when constructed and automatically release them when destructed.
class ObjectSelector {
public:
	ObjectSelector(HDC hdc, HGDIOBJ hobj) { m_hdc = hdc; m_hOldObj = SelectObject(hdc, hobj); }
	~ObjectSelector() { m_hOldObj = SelectObject(m_hdc, m_hOldObj); }
	HGDIOBJ m_hOldObj;
	HDC m_hdc;
};

class PaletteSelector {
public:
	PaletteSelector(HDC hdc, HPALETTE hpal) { 
		m_hdc = hdc; 
		m_hOldPal = SelectPalette(hdc, hpal, FALSE); 
		RealizePalette(hdc);
	}
	~PaletteSelector() { 
		m_hOldPal = SelectPalette(m_hdc, m_hOldPal, FALSE); 
		RealizePalette(m_hdc);
	}
	HPALETTE m_hOldPal;
	HDC m_hdc;
};

class TempDC {
public:
	TempDC(HWND hwnd) { m_hdc = GetDC(hwnd); m_hwnd = hwnd; }
	~TempDC() { ReleaseDC(m_hwnd, m_hdc); }
	operator HDC() {return m_hdc;};
	HDC m_hdc;
	HWND m_hwnd;
};

// *************************************************************************
//  A Client connection involves two threads - the main one which sets up
//  connections and processes window messages and inputs, and a 
//  client-specific one which receives, decodes and draws output data 
//  from the remote server.
//  This first section contains bits which are generally called by the main
//  program thread.
// *************************************************************************

ClientConnection::ClientConnection(VNCviewerApp *pApp)
{
	Init(pApp);
}

ClientConnection::ClientConnection(VNCviewerApp *pApp, SOCKET sock) 
{
	Init(pApp);
	m_sock = sock;
	struct sockaddr_in svraddr;
	int sasize = sizeof(svraddr);
	if (getpeername(sock, (struct sockaddr *) &svraddr, 
		&sasize) != SOCKET_ERROR) {
		_stprintf(m_host, _T("%d.%d.%d.%d"), 
			svraddr.sin_addr.S_un.S_un_b.s_b1, 
			svraddr.sin_addr.S_un.S_un_b.s_b2, 
			svraddr.sin_addr.S_un.S_un_b.s_b3, 
			svraddr.sin_addr.S_un.S_un_b.s_b4);
		m_port = svraddr.sin_port;
	} else {
		_tcscpy(m_host,_T("(unknown)"));
		m_port = 0;
	};
}

ClientConnection::ClientConnection(VNCviewerApp *pApp, LPTSTR host, int port)
{
	Init(pApp);
	_tcsncpy(m_host, host, 256);
	m_port = port;
}

void ClientConnection::Init(VNCviewerApp *pApp)
{
	m_hwnd = 0;
	m_desktopName = NULL;
	m_port = -1;
	m_netbuf = NULL;
	m_netbufsize = 0;
	m_hwndNextViewer = NULL;	
	m_pApp = pApp;
	m_dormant = false;
	m_hBitmapDC = NULL;
	m_hBitmap = NULL;
	m_hPalette = NULL;

	// We take the initial conn options from the application defaults
	m_opts = m_pApp->m_options;

	m_sock = INVALID_SOCKET;
	m_bKillThread = false;
	m_threadStarted = true;
	m_running = false;
	m_pendingFormatChange = false;

	m_hScrollPos = 0; m_vScrollPos = 0; m_barheight=0;

	m_fullScreenMode = false;

	// Create a buffer for various network operations
	CheckBufferSize(INITIALNETBUFSIZE);

	m_pApp->RegisterConnection(this);

	UpdateWindow(m_hwnd);
}

// 
// Run() creates the connection if necessary, does the initial negotiations
// and then starts the thread running which does the output (update) processing.
// If Run throws an Exception, the caller must delete the ClientConnection object.
//

void ClientConnection::Run()
{
	int ecode;
    __try {
		// Get the host name and port if we haven't got it
		if (m_port == -1) 
			GetConnectDetails();
		
		// Connect if we're not already connected
		if (m_sock == INVALID_SOCKET) 
			Connect();
		
		SetSocketOptions();
		
		NegotiateProtocolVersion();
		
		Authenticate();
		
		// Set up widows etc 
		CreateDisplay();
		
		SendClientInit();
		
		ReadServerInit();
		
		CreateLocalFramebuffer();
		
		SetupPixelFormat();
		
		SetFormatAndEncodings();
		
		
        // This starts the worker thread.
        // The rest of the processing continues in run_undetached.
        start_undetached();
		
    } __except (ecode = GetExceptionCode( ), 
		(ecode == VNC_EXC_HOSTNAME) || 
		(ecode == VNC_EXC_CONNECT) ||
		(ecode == VNC_EXC_AUTHFAIL) ) {
        switch (ecode) {
        case VNC_EXC_HOSTNAME:
            MessageBox(NULL, _T("Server address not found"), 
                _T("Connection failed"), MB_OK | MB_TOPMOST | MB_ICONEXCLAMATION);
			break;
		case VNC_EXC_CONNECT:
            MessageBox(NULL, _T("Could not connect to server"), 
                _T("Connection failed"), MB_OK | MB_TOPMOST | MB_ICONEXCLAMATION);
            break;
		case VNC_EXC_AUTHFAIL:
			MessageBox(NULL, _T("Authentication failed"), 
                _T("VNC authentication"), MB_OK | MB_TOPMOST | MB_ICONEXCLAMATION);
            break;
        }
		RaiseException(ecode, 0, 0, 0);
		
    }
    
}

void ClientConnection::CreateDisplay() 
{
	// Create the window
	WNDCLASS wndclass;

	wndclass.style			= 0;
	wndclass.lpfnWndProc	= ClientConnection::WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= m_pApp->m_instance;
	wndclass.hIcon			= LoadIcon(m_pApp->m_instance, MAKEINTRESOURCE(IDI_MAINICON));
	wndclass.hCursor		= LoadCursor(m_pApp->m_instance, MAKEINTRESOURCE(IDC_DOTCURSOR));
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
    wndclass.lpszMenuName	= (const TCHAR *) NULL;
	wndclass.lpszClassName	= VWR_WND_CLASS_NAME;

	RegisterClass(&wndclass);

#ifdef UNDER_CE
	const DWORD winstyle = WS_VSCROLL | WS_HSCROLL;
#else
	const DWORD winstyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | 
	  WS_MINIMIZEBOX | WS_THICKFRAME | WS_VSCROLL | WS_HSCROLL;
#endif

	m_hwnd = CreateWindow(VWR_WND_CLASS_NAME,
			      _T("VNCviewer"),
			      winstyle,
			      CW_USEDEFAULT,
			      CW_USEDEFAULT,
			      CW_USEDEFAULT,       // x-size
			      CW_USEDEFAULT,       // y-size
			      NULL,                // Parent handle
			      NULL,                // Menu handle
			      m_pApp->m_instance,
			      NULL);

	ShowWindow(m_hwnd, SW_HIDE);

	// record which client created this window
	SetWindowLong(m_hwnd, GWL_USERDATA, (LONG) this);

	// Create a memory DC which we'll use for drawing to
	// the local framebuffer
	m_hBitmapDC = CreateCompatibleDC(NULL);

#ifndef UNDER_CE
	// Set a suitable palette up
	if (GetDeviceCaps(m_hBitmapDC, RASTERCAPS) & RC_PALETTE) {
		log.Print(3, _T("Palette-based display - %d entries, %d reserved\n"), 
			GetDeviceCaps(m_hBitmapDC, SIZEPALETTE), GetDeviceCaps(m_hBitmapDC, NUMRESERVED));
		BYTE buf[sizeof(LOGPALETTE)+216*sizeof(PALETTEENTRY)];
		LOGPALETTE *plp = (LOGPALETTE *) buf;
		int pepos = 0;
		for (int r = 5; r >= 0; r--) {
			for (int g = 5; g >= 0; g--) {
				for (int b = 5; b >= 0; b--) {
					plp->palPalEntry[pepos].peRed   = r * 255 / 5; 	
					plp->palPalEntry[pepos].peGreen = g * 255 / 5;
					plp->palPalEntry[pepos].peBlue  = b * 255 / 5;
					plp->palPalEntry[pepos].peFlags  = NULL;
					pepos++;
				}
			}
		}
		plp->palVersion = 0x300;
		plp->palNumEntries = 216;
		m_hPalette = CreatePalette(plp);
	}
#endif

#ifndef UNDER_CE
	// Add stuff to System menu
	HMENU hsysmenu = GetSystemMenu(m_hwnd, FALSE);


	if (!m_opts.m_restricted) {
		AppendMenu(hsysmenu, MF_STRING, IDC_OPTIONBUTTON,	_T("Connection &options..."));
		AppendMenu(hsysmenu, MF_STRING, ID_CONN_ABOUT,		_T("Connection &info"));
		AppendMenu(hsysmenu, MF_STRING, ID_REQUEST_REFRESH,	_T("Request screen &refresh"));

		AppendMenu(hsysmenu, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hsysmenu, MF_STRING, ID_FULLSCREEN, _T("&Full screen"));
		AppendMenu(hsysmenu, MF_SEPARATOR, NULL, NULL);
 		AppendMenu(hsysmenu, MF_STRING, ID_CONN_CTLALTDEL,	_T("Send Ctl-Alt-Del"));
		AppendMenu(hsysmenu, MF_STRING, ID_CONN_CTLDOWN,	_T("Ctrl Down"));
		AppendMenu(hsysmenu, MF_STRING, ID_CONN_CTLUP,		_T("Ctrl Up"));
		AppendMenu(hsysmenu, MF_STRING, ID_CONN_ALTDOWN,	_T("Alt Down"));
		AppendMenu(hsysmenu, MF_STRING, ID_CONN_ALTUP,		_T("Alt Up"));
		AppendMenu(hsysmenu, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hsysmenu, MF_STRING, ID_NEWCONN,			_T("Ne&w connection..."));
	}
    AppendMenu(hsysmenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hsysmenu, MF_STRING, IDD_APP_ABOUT,		_T("&About VNCviewer..."));
	if (m_opts.m_listening) {
		AppendMenu(hsysmenu, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hsysmenu, MF_STRING, ID_CLOSEDAEMON, _T("Close listening &daemon"));
	}
	DrawMenuBar(m_hwnd);

#else

	// CE doesn't have a system menu
	// Create a Rebar control instead
	m_hbands = CommandBands_Create(m_pApp->m_instance, m_hwnd, 
		ID_COMMANDBANDS, RBS_VARHEIGHT | RBS_BANDBORDERS, NULL);

	REBARBANDINFO arbbi[1];
	arbbi[0].cbSize = sizeof(REBARBANDINFO); 
	arbbi[0].fMask = RBBIM_ID | RBBIM_SIZE ;
	arbbi[0].wID = ID_MENUBAND;
	arbbi[0].cx = 100;
	CommandBands_AddBands(m_hbands, m_pApp->m_instance, 1, arbbi);

	HWND hwnd = CommandBands_GetCommandBar(m_hbands, 0);
	CommandBar_InsertMenubar(hwnd, m_pApp->m_instance, IDR_COMMANDMENU, 0);
#endif

	// Set up clipboard watching
#ifndef UNDER_CE
	// We want to know when the clipboard changes, so
	// insert ourselves in the viewer chain. But doing
	// this will cause us to be notified immediately of
	// the current state.
	// We don't want to send that.
	m_initialClipboardSeen = false;
	m_hwndNextViewer = SetClipboardViewer(m_hwnd); 	
#endif
}

void ClientConnection::GetConnectDetails()
{
		SessionDialog sessdlg(&m_opts);
		if (!sessdlg.DoDialog()) {
			RaiseException( VNC_EXC_QUIETCLOSE, 0, 0, 0);
		}
		_tcsncpy(m_host, sessdlg.m_host, 256);
		m_port = sessdlg.m_port;
}

void ClientConnection::Connect()
{
	struct sockaddr_in thataddr;
	int res;
	
	m_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET) {
        RaiseException( VNC_EXC_SOCKET, 0, 0, 0);
    }
	int one = 1;
	
	__try {
	
        char ansihost[256];
        int origlen = _tcslen(m_host);
        int newlen = WideCharToMultiByte(
            CP_ACP,         // code page
            0,         // performance and mapping flags
            m_host, // address of wide-character string
            origlen,       // number of characters in string
            ansihost,  // address of buffer for new string
            255,       // size of buffer
            NULL, NULL );
 
        ansihost[newlen]= '\0';
        // The host may be specified as a dotted address "a.b.c.d"
		// Try that first
		thataddr.sin_addr.s_addr = inet_addr(ansihost);
		
		// If it wasn't one of those, do gethostbyname
		if (thataddr.sin_addr.s_addr == INADDR_NONE) {
			LPHOSTENT lphost;
			lphost = gethostbyname(ansihost);
			
			if (lphost == NULL) { 
                RaiseException( VNC_EXC_HOSTNAME, 0, 0, 0);
			};
			thataddr.sin_addr.s_addr = ((LPIN_ADDR) lphost->h_addr)->s_addr;
		};
		
		thataddr.sin_family = AF_INET;
		thataddr.sin_port = htons(m_port);
		res = connect(m_sock, (LPSOCKADDR) &thataddr, sizeof(thataddr));
		if (res == SOCKET_ERROR) RaiseException( VNC_EXC_CONNECT, 0, 0, 0);
	} __except ( EXCEPTION_EXECUTE_HANDLER ) {
		if (m_sock) closesocket(m_sock);
		m_sock = 0;
		m_pApp->DeregisterConnection(this);
		SendMessage(m_hwnd, WM_CLOSE,0,0);
		RaiseException( GetExceptionCode(), 0, 0, 0);;
	}
}

void ClientConnection::SetSocketOptions() {
	// Disable Nagle's algorithm
	BOOL nodelayval = TRUE;
	if (setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (const char *) &nodelayval, sizeof(BOOL)))
		 RaiseException( VNC_EXC_SOCKET, 0, 0, 0);
}

void ClientConnection::NegotiateProtocolVersion()
{
	rfbProtocolVersionMsg pv;

   /* if the connection is immediately closed, don't report anything, so
       that pmw's monitor can make test connections */

    __try {
		ReadExact(pv, sz_rfbProtocolVersionMsg);
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		log.Print(0, _T("Error reading protocol version\n"));
		RaiseException(VNC_EXC_QUIETCLOSE,0,0,0);
	}

    pv[sz_rfbProtocolVersionMsg] = 0;

	// XXX This is a hack.  Under CE we just return to the server the
	// version number it gives us without parsing it.  
	// Too much hassle replacing sscanf for now. Fix this!
#ifdef UNDER_CE
	m_majorVersion = rfbProtocolMajorVersion;
	m_minorVersion = rfbProtocolMinorVersion;
#else
    if (sscanf(pv,rfbProtocolVersionFormat,&m_majorVersion,&m_minorVersion) != 2) {
		RaiseException(VNC_EXC_INVALID,0,0,0);
    }
    log.Print(0, _T("RFB server supports protocol version %d.%d\n"),
	    m_majorVersion,m_minorVersion);

    if ((m_majorVersion == 3) && (m_minorVersion < 3)) {
		
        /* if server is 3.2 we can't use the new authentication */
		log.Print(0, _T("Can't use IDEA authentication\n"));
        /* This will be reported later if authentication is requested*/

    } else {
		
        /* any other server version, just tell the server what we want */
		m_majorVersion = rfbProtocolMajorVersion;
		m_minorVersion = rfbProtocolMinorVersion;

    }

    sprintf(pv,rfbProtocolVersionFormat,m_majorVersion,m_minorVersion);
#endif

    WriteExact(pv, sz_rfbProtocolVersionMsg);

	log.Print(0, _T("Connected to RFB server, using protocol version %d.%d\n"),
		rfbProtocolMajorVersion, rfbProtocolMinorVersion);
}

void ClientConnection::Authenticate()
{
	CARD32 authScheme, reasonLen, authResult;
    CARD8 challenge[CHALLENGESIZE];
	
	ReadExact((char *)&authScheme, 4);
    authScheme = Swap32IfLE(authScheme);
	
    switch (authScheme) {
		
    case rfbConnFailed:
		ReadExact((char *)&reasonLen, 4);
		reasonLen = Swap32IfLE(reasonLen);
		
		CheckBufferSize(reasonLen+1);
		ReadString(m_netbuf, reasonLen);

		log.Print(0, _T("RFB connection failed, reason: %s\n"), m_netbuf);		
		RaiseException(VNC_EXC_CONNFAIL,0,0,0);
		break;
    case rfbNoAuth:
		log.Print(0, _T("No authentication needed\n"));
		break;
		
    case rfbVncAuth:
		{
            if ((m_majorVersion == 3) && (m_minorVersion < 3)) {
                /* if server is 3.2 we can't use the new authentication */
                log.Print(0, _T("Can't use IDEA authentication\n"));

                MessageBox(NULL, 
                    _T("Sorry - this server uses an older authentication scheme\n\r")
                    _T("which is no longer supported."), 
                    _T("Protocol Version error"), 
                    MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);

                RaiseException(VNC_EXC_UNIMPLEMENTED,0,0,0);
            }

			ReadExact((char *)challenge, CHALLENGESIZE);
			
			AuthDialog ad;
			ad.DoDialog();
			char passwd[256];
#ifndef UNDER_CE
			strcpy(passwd, ad.m_passwd);
#else
			// CE will return a wide string from dialog box.
			int origlen = _tcslen(ad.m_passwd);
            int newlen = WideCharToMultiByte(
                CP_ACP, 0, ad.m_passwd, origlen,  passwd, 255, 
                NULL, NULL );
             passwd[newlen]= '\0';
#endif
			if (strlen(passwd) == 0) {
				log.Print(0, _T("Password had zero length\n"));
				RaiseException(VNC_EXC_USERERROR,0,0,0);
			}
			if (strlen(passwd) > 8) {
				passwd[8] = '\0';
			}
    		
			vncEncryptBytes(challenge, passwd);
			
			/* Lose the password from memory */
			for (int i=0; i< (int) strlen(passwd); i++) {
				passwd[i] = '\0';
			}
			
			WriteExact((char *) challenge, CHALLENGESIZE);
			ReadExact((char *) &authResult, 4);
			
			authResult = Swap32IfLE(authResult);
			
			switch (authResult) {
			case rfbVncAuthOK:
				log.Print(0, _T("VNC authentication succeeded\n"));
				break;
			case rfbVncAuthFailed:
				log.Print(0, _T("VNC authentication failed!\n"));
				RaiseException(VNC_EXC_AUTHFAIL,0,0,0);
			case rfbVncAuthTooMany:
				log.Print(0, _T("Too many attempts!\n"));
				RaiseException(VNC_EXC_AUTHFAIL,0,0,0);
				break;
			default:
				log.Print(0, _T("Unknown VNC authentication result: %d\n"),
					(int)authResult);
				RaiseException(VNC_EXC_UNIMPLEMENTED,0,0,0);
			}
			break;
		}
		
	default:
		log.Print(0, _T("Unknown authentication scheme from RFB server: %d\n"),
			(int)authScheme);
		RaiseException(VNC_EXC_UNIMPLEMENTED,0,0,0);
    }
}

void ClientConnection::SendClientInit()
{
    rfbClientInitMsg ci;
	ci.shared = m_opts.m_Shared;

    WriteExact((char *)&ci, sz_rfbClientInitMsg);
}

void ClientConnection::ReadServerInit()
{
    ReadExact((char *)&m_si, sz_rfbServerInitMsg);
	
    m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
    m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
    m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
    m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
    m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
    m_si.nameLength = Swap32IfLE(m_si.nameLength);
	
    m_desktopName = new TCHAR[m_si.nameLength + 2];

#ifdef UNDER_CE
    char *deskNameBuf = new char[m_si.nameLength + 2];

	ReadString(deskNameBuf, m_si.nameLength);
    
	MultiByteToWideChar( CP_ACP,   MB_PRECOMPOSED, 
			     deskNameBuf, m_si.nameLength,
			     m_desktopName, m_si.nameLength+1);
    delete deskNameBuf;
#else
    ReadString(m_desktopName, m_si.nameLength);
#endif
    
	SetWindowText(m_hwnd, m_desktopName);	

	PaletteSelector p(m_hBitmapDC, m_hPalette);
	
	log.Print(0, _T("Desktop name \"%s\"\n"),m_desktopName);
	log.Print(1, _T("Geometry %d x %d depth %d\n"),
		m_si.framebufferWidth, m_si.framebufferHeight, m_si.format.depth );
	SetWindowText(m_hwnd, m_desktopName);	

	// Find how large the desktop work area is
	RECT workrect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workrect, 0);
	int workwidth = workrect.right -  workrect.left;
	int workheight = workrect.bottom - workrect.top;
	log.Print(2, _T("Screen work area is %d x %d\n"), workwidth, workheight);

	// Size the window.
	// First we find out how large a window would be needed to hold the whole
	// remote screen image.
	RECT fullwinrect;
	SetRect(&fullwinrect, 0, 0, m_si.framebufferWidth, m_si.framebufferHeight);
	AdjustWindowRectEx(&fullwinrect, 
		GetWindowLong(m_hwnd, GWL_STYLE), GetWindowLong(m_hwnd, GWL_EXSTYLE), FALSE);
	UINT bandheight = CommandBands_Height(m_hbands);
	m_fullwinwidth = fullwinrect.right - fullwinrect.left;
	m_fullwinheight = fullwinrect.bottom - fullwinrect.top + bandheight ;

	// Then we use either this, or the screen size, whichever is smaller
	m_winwidth  = min(m_fullwinwidth,  workwidth);
	m_winheight = min(m_fullwinheight, workheight);
/*	DON'T RESIZE IT
	SetWindowPos(m_hwnd, HWND_TOP,
		workrect.left + (workwidth-m_winwidth) / 2,
		workrect.top + (workheight-m_winheight) / 2,
		m_winwidth, m_winheight, SWP_SHOWWINDOW);
*/
	ShowWindow(m_hwnd,SW_SHOWNORMAL);
	SetForegroundWindow(m_hwnd);
}

// We keep a local copy of the whole screen.  This is not sctrictly necessary
// for VNC, but makes scrolling & deiconifying much smoother.

void ClientConnection::CreateLocalFramebuffer() {
	// We create a bitmap which has the same pixel characteristics as
	// the local display, in the hope that blitting will be faster.
	TempDC hdc(m_hwnd);
	m_hBitmap = ::CreateCompatibleBitmap(hdc, 
									m_si.framebufferWidth, 
									m_si.framebufferHeight);

	if (m_hBitmap == NULL)
		RaiseException(VNC_EXC_GRAPHICS,0,0,0);
	// Select this bitmap into the DC with an appropriate palette
	ObjectSelector b(m_hBitmapDC, m_hBitmap);
	PaletteSelector p(m_hBitmapDC, m_hPalette);

	// Put a "please wait" message up initially
    RECT rect;
	SetRect(&rect, 0,0, m_si.framebufferWidth, m_si.framebufferHeight);
	COLORREF bgcol = RGB(0xcc, 0xcc, 0xcc);
	FillSolidRect(&rect, bgcol);
	
	COLORREF oldbgcol  = SetBkColor(  m_hBitmapDC, bgcol);
	COLORREF oldtxtcol = SetTextColor(m_hBitmapDC, RGB(0,0,64));
	rect.right = m_si.framebufferWidth / 2;
	rect.bottom = m_si.framebufferHeight / 2;

    DrawText (m_hBitmapDC, _T("Please wait - initial screen loading"), -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	SetBkColor(  m_hBitmapDC, oldbgcol);
	SetTextColor(m_hBitmapDC, oldtxtcol);

	InvalidateRect(m_hwnd, NULL, FALSE);
}

void ClientConnection::SetupPixelFormat() {
	// Have we requested a reduction to 8-bit?
    if (m_opts.m_Use8Bit) {		
      
		log.Print(2, _T("Requesting 8-bit truecolour\n"));  
		m_myFormat = vnc8bitFormat;
    
		// We don't support colormaps so we'll ask the server to convert
    } else if (!m_si.format.trueColour) {
        
        // We'll just request a standard 16-bit truecolor
        log.Print(2, _T("Requesting 16-bit truecolour\n"));
        m_myFormat = vnc16bitFormat;
        
    } else {

		// Normally we just use the sever's format suggestion
		m_myFormat = m_si.format;

		// It's silly requesting more bits than our current display has, but
		// in fact it doesn't usually amount to much on the network.
		// Windows doesn't support 8-bit truecolour.
		// If our display is palette-based, we want more than 8 bit anyway,
		// unless we're going to start doing palette stuff at the server.
		// So the main use would be a 24-bit true-colour desktop being viewed
		// on a 16-bit true-colour display, and unless you have lots of images
		// and hence lots of raw-encoded stuff, the size of the pixel is not
		// going to make much difference.
		//   We therefore don't bother with any restrictions, but here's the
		// start of the code if we wanted to do it.

		if (false) {
		
			// Get a DC for the root window
			TempDC hrootdc(NULL);
			int localBitsPerPixel = GetDeviceCaps(hrootdc, BITSPIXEL);
			int localRasterCaps	  = GetDeviceCaps(hrootdc, RASTERCAPS);
			log.Print(2, _T("Memory DC has depth of %d and %s pallete-based.\n"), 
				localBitsPerPixel, (localRasterCaps & RC_PALETTE) ? "is" : "is not");
			
			// If we're using truecolor, and the server has more bits than we do
			if ( (localBitsPerPixel > m_myFormat.depth) && 
				! (localRasterCaps & RC_PALETTE)) {
				m_myFormat.depth = localBitsPerPixel;

				// create a bitmap compatible with the current display
				// call GetDIBits twice to get the colour info.
				// set colour masks and shifts
				
			}
		}
	}

	// The endian will be set before sending
}

void ClientConnection::SetFormatAndEncodings()
{
	// Set pixel format to myFormat
    
	rfbSetPixelFormatMsg spf;

    spf.type = rfbSetPixelFormat;
    spf.format = m_myFormat;
    spf.format.redMax = Swap16IfLE(spf.format.redMax);
    spf.format.greenMax = Swap16IfLE(spf.format.greenMax);
    spf.format.blueMax = Swap16IfLE(spf.format.blueMax);
	spf.format.bigEndian = 0;

    WriteExact((char *)&spf, sz_rfbSetPixelFormatMsg);

    // The number of bytes required to hold at least one pixel.
	m_minPixelBytes = (m_myFormat.bitsPerPixel + 7) >> 3;

	// Set encodings
    char buf[sz_rfbSetEncodingsMsg + MAX_ENCODINGS * 4];
    rfbSetEncodingsMsg *se = (rfbSetEncodingsMsg *)buf;
    CARD32 *encs = (CARD32 *)(&buf[sz_rfbSetEncodingsMsg]);
    int len = 0;
	
    se->type = rfbSetEncodings;
    se->nEncodings = 0;

	// Put the preferred encoding first, and change it if the
	// preferred encoding is not actually usable.
	for (int i = LASTENCODING; i >= rfbEncodingRaw; i--)
	{
		if (m_opts.m_PreferredEncoding == i) {
			if (m_opts.m_UseEnc[i]) {
				encs[se->nEncodings++] = Swap32IfLE(i);
			} else {
				m_opts.m_PreferredEncoding--;
			}
		}
	}

	// Now we go through and put in all the other encodings in order.
	// We do rather assume that the most recent encoding is the most
	// desirable!
	for (i = LASTENCODING; i >= rfbEncodingRaw; i--)
	{
		if ( (m_opts.m_PreferredEncoding != i) &&
			 (m_opts.m_UseEnc[i]))
		{
			encs[se->nEncodings++] = Swap32IfLE(i);
		}
	}

    len = sz_rfbSetEncodingsMsg + se->nEncodings * 4;
	
    se->nEncodings = Swap16IfLE(se->nEncodings);
	
    WriteExact((char *) buf, len);


}

// Closing down the connection.
// Close the socket, kill the thread.
void ClientConnection::KillThread()
{
	m_bKillThread = true;
	m_running = false;

	if (m_sock != INVALID_SOCKET) {
		shutdown(m_sock, SD_BOTH);
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
	}
}


ClientConnection::~ClientConnection()
{
	if (m_hwnd != 0)
		DestroyWindow(m_hwnd);

	if (m_sock != INVALID_SOCKET) {
		shutdown(m_sock, SD_BOTH);
		closesocket(m_sock);
		m_sock = INVALID_SOCKET;
	}

	if (m_desktopName != NULL) delete [] m_desktopName;
	delete [] m_netbuf;
	DeleteDC(m_hBitmapDC);
	if (m_hBitmap != NULL)
		DeleteObject(m_hBitmap);
	if (m_hBitmapDC != NULL)
		DeleteObject(m_hBitmapDC);
	if (m_hPalette != NULL)
		DeleteObject(m_hPalette);
	
	m_pApp->DeregisterConnection(this);
}

// You can specify a dx & dy outside the limits; the return value will
// tell you whether it actually scrolled.
bool ClientConnection::ScrollScreen(int dx, int dy) 
{
	dx = max(dx, -m_hScrollPos);
	//dx = min(dx, m_hScrollMax-(m_cliwidth-1)-m_hScrollPos);
	dx = min(dx, m_hScrollMax-(m_cliwidth)-m_hScrollPos);
	dy = max(dy, -m_vScrollPos);
	//dy = min(dy, m_vScrollMax-(m_cliheight-1)-m_vScrollPos);
	dy = min(dy, m_vScrollMax-(m_cliheight)-m_vScrollPos);
	if (dx || dy) {
		m_hScrollPos += dx;
		m_vScrollPos += dy;
		RECT clirect;
		GetClientRect(m_hwnd, &clirect);
		ScrollWindowEx(m_hwnd, -dx, -dy, NULL, &clirect, NULL, NULL,  SW_INVALIDATE);
		UpdateScrollbars();
		UpdateWindow(m_hwnd);
		return true;
	}
	return false;
}

// Process windows messages

LRESULT CALLBACK ClientConnection::WndProc(HWND hwnd, UINT iMsg, 
					   WPARAM wParam, LPARAM lParam) {
	
	// This is a static method, so we don't know which instantiation we're 
	// dealing with.  But we've stored a 'pseudo-this' in the window data.
	ClientConnection *_this = (ClientConnection *) GetWindowLong(hwnd, GWL_USERDATA);

	switch (iMsg) {

	case WM_CREATE:
		return 0;

	case WM_PAINT:
		_this->DoBlit();
		return 0;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
        // Alt-click = right click
        if (GetKeyState(VK_MENU) < 0) {
            wParam = (wParam & ~MK_LBUTTON) | MK_RBUTTON;
        }
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		{
			if (!_this->m_running) return 0;
			if (GetFocus() != hwnd) return 0;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam)-_this->m_barheight;
#ifndef UNDER_CE
			if (_this->InFullScreenMode()) {
				if (_this->BumpScroll(x,y))
					return 0;
			}
#endif
			if ( _this->m_opts.m_ViewOnly) return 0;
			_this->ProcessPointerEvent(x,y,wParam);
			return 0;
		}

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		{
			if (!_this->m_running) return 0;
			if ( _this->m_opts.m_ViewOnly) return 0;
            _this->ProcessKeyEvent((int) wParam, (DWORD) lParam);
			return 0;
		}

	case WM_CHAR:
	case WM_SYSCHAR:
#ifdef UNDER_CE
        {
            int key = wParam;
            log.Print(4,_T("CHAR msg : %02x\n"), key);
            // Control keys which are in the Keymap table will already
            // have been handled.
            if (key == 0x0D  ||  // return
                key == 0x20 ||   // space
                key == 0x08)     // backspace
                return 0;

            if (key < 32) key += 64;  // map ctrl-keys onto alphabet
            if (key > 32 && key < 127) {
                _this->SendKeyEvent(wParam & 0xff, true);
                _this->SendKeyEvent(wParam & 0xff, false);
            }
            return 0;
        }
#endif
	case WM_DEADCHAR:
	case WM_SYSDEADCHAR:
	  return 0;

	case WM_SETFOCUS:
		if (_this->InFullScreenMode())
			SetWindowPos(hwnd, HWND_TOPMOST, 0,0,100,100, SWP_NOMOVE | SWP_NOSIZE);
		return 0;
	// Cacnel modifiers when we lose focus
	case WM_KILLFOCUS:
		{
			if (!_this->m_running) return 0;
			if (_this->InFullScreenMode()) {
				// We must top being topmost, but we want to choose our
				// position carefully.
				HWND foreground = GetForegroundWindow();
				HWND hwndafter = NULL;
				if ((foreground == NULL) || 
					(GetWindowLong(foreground, GWL_EXSTYLE) & WS_EX_TOPMOST)) {
					hwndafter = HWND_NOTOPMOST;
				} else {
					hwndafter = GetWindow(foreground, GW_HWNDNEXT); 
				}

				SetWindowPos(hwnd, hwndafter, 0,0,100,100, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}
			log.Print(6, _T("Losing focus - cancelling modifiers\n"));
			_this->SendKeyEvent(XK_Alt_L,     false);
			_this->SendKeyEvent(XK_Control_L, false);
			_this->SendKeyEvent(XK_Shift_L,   false);
			_this->SendKeyEvent(XK_Alt_R,     false);
			_this->SendKeyEvent(XK_Control_R, false);
			_this->SendKeyEvent(XK_Shift_R,   false);
			return 0;
		}
	case WM_CLOSE:
		{

			// Close the worker thread as well
			_this->KillThread();
			DestroyWindow(hwnd);
			return 0;
		}

	case WM_DESTROY:
		{
#ifndef UNDER_CE
			// Remove us from the clipboard viewer chain
			BOOL res = ChangeClipboardChain( hwnd, _this->m_hwndNextViewer);
#endif
			
			_this->m_hwnd = 0;
			// We are currently in the main thread.
			// The worker thread should be about to finish if
			// it hasn't already. Wait for it.
			__try {
				void *p;
				_this->join(&p);  // After joining, _this is no longer valid
			} __except (OMNI_EXC_THREAD_INVALID) {
				// The thread probably hasn't been started yet,
			}
			
			return 0;
		}

	case WM_SIZE:
		{
			// Calculate window dimensions
			RECT rect;
			GetWindowRect(hwnd, &rect);
			// update these for the record
			_this->m_winwidth = rect.right - rect.left;
			_this->m_winheight = rect.bottom - rect.top;

			// If the current window size would be large enough to hold the
			// whole screen without scrollbars, or if we're full-screen,
			// we turn them off.  Under CE, the scroll bars are unchangeable.

			#ifndef UNDER_CE
			if (_this->InFullScreenMode() ||
				_this->m_winwidth  >= _this->m_fullwinwidth  &&
				_this->m_winheight >= _this->m_fullwinheight ) {
				ShowScrollBar(hwnd, SB_HORZ, FALSE);
				ShowScrollBar(hwnd, SB_VERT, FALSE);
			} else {
				ShowScrollBar(hwnd, SB_HORZ, TRUE);
				ShowScrollBar(hwnd, SB_VERT, TRUE);
			}
			#endif

            // Update these for the record
			// And consider that in full-screen mode the window
			// is actually bigger than the remote screen.
			GetClientRect(hwnd, &rect);
			_this->m_barheight = CommandBands_Height (_this->m_hbands);
			_this->m_cliwidth = min( rect.right - rect.left, 
									 _this->m_si.framebufferWidth );
			_this->m_cliheight = min( rect.bottom - (rect.top + _this->m_barheight),
									 _this->m_si.framebufferHeight );

			_this->m_hScrollMax = _this->m_si.framebufferWidth;
			_this->m_vScrollMax = _this->m_si.framebufferHeight;
            
			int newhpos, newvpos;
			newhpos = max(0, min(_this->m_hScrollPos, 
								 _this->m_hScrollMax - max(_this->m_cliwidth, 0)));
			newvpos = max(0, min(_this->m_vScrollPos, 
				                 _this->m_vScrollMax - max(_this->m_cliheight, 0)));

			ScrollWindowEx(hwnd, _this->m_hScrollPos-newhpos, _this->m_vScrollPos-newvpos,
				NULL, &rect, NULL, NULL,  SW_INVALIDATE);
			
			_this->m_hScrollPos = newhpos;
			_this->m_vScrollPos = newvpos;
           	_this->UpdateScrollbars();

			return 0;
		}

	case WM_HSCROLL:
		{
			int dx = 0;
			int pos = HIWORD(wParam);
			switch (LOWORD(wParam)) {
			case SB_LINEUP:
				dx = -2; break;
			case SB_LINEDOWN:
				dx = 2; break;
			case SB_PAGEUP:
				dx = _this->m_cliwidth * -1/4; break;
			case SB_PAGEDOWN:
				dx = _this->m_cliwidth * 1/4; break;
			case SB_THUMBPOSITION:
				dx = pos - _this->m_hScrollPos;
			case SB_THUMBTRACK:
				dx = pos - _this->m_hScrollPos;
			}
			_this->ScrollScreen(dx,0);
			return 0;
		}

	case WM_VSCROLL:
		{
			int dy = 0;
			int pos = HIWORD(wParam);
			switch (LOWORD(wParam)) {
			case SB_LINEUP:
				dy = -2; break;
			case SB_LINEDOWN:
				dy = 2; break;
			case SB_PAGEUP:
				dy = _this->m_cliheight * -1/4; break;
			case SB_PAGEDOWN:
				dy = _this->m_cliheight * 1/4; break;
			case SB_THUMBPOSITION:
				dy = pos - _this->m_vScrollPos;
			case SB_THUMBTRACK:
				dy = pos - _this->m_vScrollPos;
			}
			_this->ScrollScreen(0,dy);
			return 0;
		}

    case WM_QUERYNEWPALETTE:
        {
			TempDC hDC(hwnd);
			
			// Select and realize hPalette
			PaletteSelector p(hDC, _this->m_hPalette);
			InvalidateRect(hwnd, NULL, FALSE);
			UpdateWindow(hwnd);

			return TRUE;
        }

	case WM_HELP:
		{
			ShowAboutBox();
			return 0;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
#ifndef UNDER_CE
			case SC_MINIMIZE:
				_this->SetDormant(true);
				break;
			case SC_RESTORE:
				_this->SetDormant(false);
				break;
			case ID_FULLSCREEN: 
				// Toggle full screen mode
				_this->SetFullScreenMode(!_this->InFullScreenMode());
				return 0;
#endif
            case ID_NEWCONN:
				_this->m_pApp->NewConnection();
				return 0;
			case IDC_OPTIONBUTTON: 
				if (_this->m_opts.DoDialog(true)) {
					_this->m_pendingFormatChange = true;
				};
				return 0;
			case ID_CONN_ABOUT:
				_this->ShowConnInfo();
				return 0;
			case ID_CONN_CLOSE:
				PostMessage(hwnd, WM_CLOSE, 0,0);
				return 0;
			case ID_REQUEST_REFRESH: 
				// Request a full-screen update
				_this->SendFullFramebufferUpdateRequest();
				return 0;

			case ID_CONN_CTLALTDEL:
				_this->SendKeyEvent(XK_Control_L, true);
				_this->SendKeyEvent(XK_Alt_L,     true);
				_this->SendKeyEvent(XK_Delete,    true);
				_this->SendKeyEvent(XK_Delete,    false);
				_this->SendKeyEvent(XK_Alt_L,     false);
				_this->SendKeyEvent(XK_Control_L, false);
				return 0;
            case ID_CONN_CTLDOWN:
                _this->SendKeyEvent(XK_Control_L, true);
                return 0;
            case ID_CONN_CTLUP:
				_this->SendKeyEvent(XK_Control_L, false);
				return 0;
			case ID_CONN_ALTDOWN:
                _this->SendKeyEvent(XK_Alt_L, true);
				return 0;
			case ID_CONN_ALTUP:
                _this->SendKeyEvent(XK_Alt_L, false);
                return 0;
			case IDD_APP_ABOUT:
				ShowAboutBox();
				return 0;
			case ID_CLOSEDAEMON:
				if (MessageBox(NULL, _T("Are you sure you want to exit?"), 
						_T("Closing VNCviewer"), 
						MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
					PostQuitMessage(0);
				return 0;
			}
			break;
		}

#ifndef UNDER_CE
	case WM_PALETTECHANGED:
		// If this application did not change the palette, select
		// and realize this application's palette
		if ((HWND) wParam != hwnd)
		{
			// Need the window's DC for SelectPalette/RealizePalette
			TempDC hDC(hwnd);
			PaletteSelector p(hDC, _this->m_hPalette);
			// When updating the colors for an inactive window,
			// UpdateColors can be called because it is faster than
			// redrawing the client area (even though the results are
			// not as good)
				#ifndef UNDER_CE
				UpdateColors(hDC);
				#else
				InvalidateRect(hwnd, NULL, FALSE);
				UpdateWindow(hwnd);
				#endif

		}
        break;


	case WM_SIZING:
		{
			// Don't allow sizing larger than framebuffer
			RECT *lprc = (LPRECT) lParam;
			switch (wParam) {
			case WMSZ_RIGHT: 
			case WMSZ_TOPRIGHT:
			case WMSZ_BOTTOMRIGHT:
				lprc->right = min(lprc->right, lprc->left + _this->m_fullwinwidth+1);
				break;
			case WMSZ_LEFT:
			case WMSZ_TOPLEFT:
			case WMSZ_BOTTOMLEFT:
				lprc->left = max(lprc->left, lprc->right - _this->m_fullwinwidth);
				break;
			}
			
			switch (wParam) {
			case WMSZ_TOP:
			case WMSZ_TOPLEFT:
			case WMSZ_TOPRIGHT:
				lprc->top = max(lprc->top, lprc->bottom - _this->m_fullwinheight);
				break;
			case WMSZ_BOTTOM:
			case WMSZ_BOTTOMLEFT:
			case WMSZ_BOTTOMRIGHT:
				lprc->bottom = min(lprc->bottom, lprc->top + _this->m_fullwinheight);
				break;
			}

			return 0;
		}
	
	case WM_SETCURSOR:
		{
			// if we have the focus, let the cursor change as normal
			if (GetFocus() == hwnd) 
				break;

			// if not, set to default system cursor
			SetCursor( LoadCursor(NULL, IDC_ARROW));
			return 0;
		}

	case WM_DRAWCLIPBOARD:
		_this->ProcessLocalClipboardChange();
		return 0;

	case WM_CHANGECBCHAIN:
		{
			// The clipboard chain is changing
			HWND hWndRemove = (HWND) wParam;     // handle of window being removed 
			HWND hWndNext = (HWND) lParam;       // handle of next window in chain 
			// If next window is closing, update our pointer.
			if (hWndRemove == _this->m_hwndNextViewer)  
				_this->m_hwndNextViewer = hWndNext;  
			// Otherwise, pass the message to the next link.  
			else if (_this->m_hwndNextViewer != NULL) 
				::SendMessage(_this->m_hwndNextViewer, WM_CHANGECBCHAIN, 
				(WPARAM) hWndRemove,  (LPARAM) hWndNext );  
			return 0;

		}
#endif
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
	
	// We know about an unused variable here.
#pragma warning(disable : 4101)
}

#pragma warning(default : 4101)

// ProcessPointerEvent takes windows positions and flags and converts 
// them into VNC ones.

inline void
ClientConnection::ProcessPointerEvent(int x, int y, DWORD keyflags) 
{
	int mask;
	if (m_opts.m_Emul3Buttons) {
		// XXX To be done:
		// If this is a left or right press, the user may be 
		// about to press the other button to emulate a middle press.
		// We need to start a timer, and if it expires without any
		// further presses, then we send the button press. 
		// If a press of the other button, or any release, comes in
		// before timer has expired, we cancel timer &take different action.
	}

	if (m_opts.m_SwapMouse) {
		mask = ( ((keyflags & MK_LBUTTON) ? rfbButton1Mask : 0) |
			((keyflags & MK_MBUTTON) ? rfbButton3Mask : 0) |
			((keyflags & MK_RBUTTON) ? rfbButton2Mask : 0)  );
	} else {
		mask = ( ((keyflags & MK_LBUTTON) ? rfbButton1Mask : 0) |
			((keyflags & MK_MBUTTON) ? rfbButton2Mask : 0) |
			((keyflags & MK_RBUTTON) ? rfbButton3Mask : 0)  );
	}
	
	__try {
		SendPointerEvent(x + m_hScrollPos, y + m_vScrollPos, mask);
	}  __except (EXCEPTION_EXECUTE_HANDLER) {
	        PostMessage(m_hwnd, WM_CLOSE, 0, 0);
	}
}

//
// SendPointerEvent.
//

inline void
ClientConnection::SendPointerEvent(int x, int y, int buttonMask)
{
    rfbPointerEventMsg pe;

    pe.type = rfbPointerEvent;
    pe.buttonMask = buttonMask;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    pe.x = Swap16IfLE(x);
    pe.y = Swap16IfLE(y);
	WriteExact((char *)&pe, sz_rfbPointerEventMsg);
}

//
// ProcessKeyEvent
//
// Normally a single Windows key event will map onto a single RFB
// key message, but this is not always the case.  Much of the stuff
// here is to handle AltGr (=Ctrl-Alt) on international keyboards.
// Example cases:
//
//    We want Ctrl-F to be sent as:
//      Ctrl-Down, F-Down, F-Up, Ctrl-Up.
//    because there is no keysym for ctrl-f, and because the ctrl
//    will already have been sent by the time we get the F.
//
//    On German keyboards, @ is produced using AltGr-Q, which is
//    Ctrl-Alt-Q.  But @ is a valid keysym in its own right, and when
//    a German user types this combination, he doesn't mean Ctrl-@.
//    So for this we will send, in total:
//
//      Ctrl-Down, Alt-Down,   
//                 (when we get the AltGr pressed)
//
//      Alt-Up, Ctrl-Up, @-Down, Ctrl-Down, Alt-Down 
//                 (when we discover that this is @ being pressed)
//
//      Alt-Up, Ctrl-Up, @-Up, Ctrl-Down, Alt-Down
//                 (when we discover that this is @ being released)
//
//      Alt-Up, Ctrl-Up
//                 (when the AltGr is released)

inline void ClientConnection::ProcessKeyEvent(int virtkey, DWORD keyData)
{
    bool down = ((keyData & 0x80000000l) == 0);

    // if virtkey found in mapping table, send X equivalent
    // else
    //   try to convert directly to ascii
    //   if result is in range supported by X keysyms,
    //      raise any modifiers, send it, then restore mods
    //   else
    //      calculate what the ascii would be without mods
    //      send that

#ifdef _DEBUG
#ifdef UNDER_CE
	char *keyname="";
#else
    char keyname[32];
    if (GetKeyNameText(  keyData,keyname, 31)) {
        log.Print(4, _T("Process key: %s (keyData %04x): "), keyname, keyData);
    };
#endif
#endif 

    __try {
    KeyActionSpec kas = m_keymap.PCtoX(virtkey, keyData);    

    if (kas.releaseModifiers & KEYMAP_LCONTROL) {
        SendKeyEvent(XK_Control_L, false );
        log.Print(5, _T("fake L Ctrl raised\n"));
    }
    if (kas.releaseModifiers & KEYMAP_LALT) {
        SendKeyEvent(XK_Alt_L, false );
        log.Print(5, _T("fake L Alt raised\n"));
    }
    if (kas.releaseModifiers & KEYMAP_RCONTROL) {
        SendKeyEvent(XK_Control_R, false );
        log.Print(5, _T("fake R Ctrl raised\n"));
    }
    if (kas.releaseModifiers & KEYMAP_RALT) {
        SendKeyEvent(XK_Alt_R, false );
        log.Print(5, _T("fake R Alt raised\n"));
    }

    for (int i = 0; kas.keycodes[i] != XK_VoidSymbol && i < MaxKeysPerKey; i++) {
        SendKeyEvent(kas.keycodes[i], down );
        log.Print(4, _T("Sent keysym %04x (%s)\n"), 
            kas.keycodes[i], down ? _T("press") : _T("release"));
    }

    if (kas.releaseModifiers & KEYMAP_RALT) {
        SendKeyEvent(XK_Alt_R, true );
        log.Print(5, _T("fake R Alt pressed\n"));
    }
    if (kas.releaseModifiers & KEYMAP_RCONTROL) {
        SendKeyEvent(XK_Control_R, true );
        log.Print(5, _T("fake R Ctrl pressed\n"));
    }
    if (kas.releaseModifiers & KEYMAP_LALT) {
        SendKeyEvent(XK_Alt_L, false );
        log.Print(5, _T("fake L Alt pressed\n"));
    }
    if (kas.releaseModifiers & KEYMAP_LCONTROL) {
        SendKeyEvent(XK_Control_L, false );
        log.Print(5, _T("fake L Ctrl pressed\n"));
    }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        PostMessage(m_hwnd, WM_CLOSE, 0, 0);
    }
}

//
// SendKeyEvent
//

inline void
ClientConnection::SendKeyEvent(CARD32 key, bool down)
{
    rfbKeyEventMsg ke;

    ke.type = rfbKeyEvent;
    ke.down = down ? 1 : 0;
    ke.key = Swap32IfLE(key);
    WriteExact((char *)&ke, sz_rfbKeyEventMsg);
    log.Print(6, _T("SendKeyEvent: key = x%04x status = %s\n"), key, 
        down ? _T("down") : _T("up"));
}

#ifndef UNDER_CE
//
// SendClientCutText
//

void ClientConnection::SendClientCutText(char *str, int len)
{
    rfbClientCutTextMsg cct;

    cct.type = rfbClientCutText;
    cct.length = Swap32IfLE(len);
    WriteExact((char *)&cct, sz_rfbClientCutTextMsg);
	WriteExact(str, len);
	log.Print(6, _T("Sent %d bytes of clipboard\n"), len);
}
#endif

// Copy any updated areas from the bitmap onto the screen.

inline void ClientConnection::DoBlit() 
{
	if (m_hBitmap == NULL) return;
	if (!m_running) return;
	omni_mutex_lock l(m_bitmapdcMutex);
				
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hwnd, &ps);
	HPALETTE hOldPal = NULL;
	// Select and realize hPalette
	PaletteSelector p(hdc, m_hPalette);

	ObjectSelector b(m_hBitmapDC, m_hBitmap);

	if (m_opts.m_delay) {
		// Display the area to be updated for debugging purposes
		COLORREF oldbgcol = SetBkColor(hdc, RGB(0,0,0));
		::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &ps.rcPaint, NULL, 0, NULL);
		SetBkColor(hdc,oldbgcol);
		::Sleep(m_pApp->m_options.m_delay);
	}
	
	if (!BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, 
		ps.rcPaint.right-ps.rcPaint.left, ps.rcPaint.bottom-ps.rcPaint.top, 
		m_hBitmapDC, ps.rcPaint.left+m_hScrollPos, ps.rcPaint.top+m_vScrollPos-m_barheight,
		SRCCOPY)) 
	{
		log.Print(0, _T("Blit error %d\n"), GetLastError());
		RaiseException(VNC_EXC_GRAPHICS,0,0,0);
	}
	

	EndPaint(m_hwnd, &ps);
}

inline void ClientConnection::UpdateScrollbars() 
{
	// We don't update the actual scrollbar info in full-screen mode
	// because it causes them to flicker.
	bool setInfo = !InFullScreenMode();

	SCROLLINFO scri;
	scri.cbSize = sizeof(scri);
	scri.fMask = SIF_ALL;
	scri.nMin = 0;
	scri.nMax = m_hScrollMax;     
	scri.nPage= m_cliwidth;
	scri.nPos = m_hScrollPos; 
	
	if (setInfo) 
		SetScrollInfo(m_hwnd, SB_HORZ, &scri, TRUE);
	
	scri.cbSize = sizeof(scri);
	scri.fMask = SIF_ALL;
	scri.nMin = 0;
	scri.nMax = m_vScrollMax;     
	scri.nPage= m_cliheight;
	scri.nPos = m_vScrollPos; 
	
	if (setInfo) 
		SetScrollInfo(m_hwnd, SB_VERT, &scri, TRUE);
}


void ClientConnection::ShowConnInfo()
{
	TCHAR buf[2048];
#ifndef UNDER_CE
	char kbdname[9];
	GetKeyboardLayoutName(kbdname);
#else
	TCHAR *kbdname = _T("(n/a)");
#endif
	_stprintf(
		buf,
		_T("Connected to: %s:\n\r")
		_T("Host: %s port: %d\n\r\n\r")
		_T("Desktop geometry: %d x %d x %d\n\r")
		_T("Using depth: %d\n\r")
		_T("Current protocol version: %d.%d\n\r\n\r")
		_T("Current keyboard name: %s\n\r"),
		m_desktopName, m_host, m_port,
		m_si.framebufferWidth, m_si.framebufferHeight, m_si.format.depth,
		m_myFormat.depth,
		m_majorVersion, m_minorVersion,
		kbdname);
	MessageBox(NULL, buf, _T("VNC connection info"), MB_ICONINFORMATION | MB_OK);
}

// ********************************************************************
//  Methods after this point are generally called by the worker thread.
//  They finish the initialisation, then chiefly read data from the server.
// ********************************************************************


void* ClientConnection::run_undetached(void* arg) {

	log.Print(9,_T("Update-processing thread started\n"));

	m_threadStarted = true;

	__try {


		UpdateWindow(m_hwnd);

		SendFullFramebufferUpdateRequest();

		m_running = true;
		
		while (!m_bKillThread) {
			
			// Look at the type of the message, but leave it in the buffer 
			CARD8 msgType;
			int bytes;
			{
			  omni_mutex_lock l(m_readMutex);
			  // on CE, we can't peek, so we read the bytes now, and one 
			  // less later
			  bytes = recv(m_sock, (char *) &msgType, 1, 0);
			}
			if (bytes == 0) {
				log.Print(0, _T("Socket closed\n") );
				RaiseException(VNC_EXC_SOCKET,0,0,0);
			}
			if (bytes < 0) {
				log.Print(3, _T("Socket error reading message: %d\n"), WSAGetLastError() );
				RaiseException(VNC_EXC_SOCKET,0,0,0);
			}
				
			switch (msgType) {
			case rfbFramebufferUpdate:
				ReadScreenUpdate();
				if (m_pendingFormatChange) {
					log.Print(3, _T("Requesting new pixel format\n") );
					rfbPixelFormat oldFormat = m_myFormat;
					SetupPixelFormat();
					SetFormatAndEncodings();
					m_pendingFormatChange = false;
					// If the pixel format has changed, request whole screen
					if (memcmp(&m_myFormat, &oldFormat, sizeof(rfbPixelFormat)) != 0) {
						SendFullFramebufferUpdateRequest();
					} else {
						SendIncrementalFramebufferUpdateRequest();
					}
				} else {
					if (!m_dormant)
						SendIncrementalFramebufferUpdateRequest();
				}
				break;
			case rfbSetColourMapEntries:
			        log.Print(3, _T("rfbSetColourMapEntries read but not supported\n") );
				RaiseException(VNC_EXC_UNIMPLEMENTED,0,0,0);
				break;
			case rfbBell:
				ReadBell();
				break;
			case rfbServerCutText:
				ReadServerCutText();
				break;
			default:
                log.Print(3, _T("Unknown message type x%02x\n"), msgType );

				RaiseException(VNC_EXC_UNIMPLEMENTED,0,0,0);
			}

		}
        
        log.Print(4, _T("Update-processing thread finishing\n") );

	} __except(EXCEPTION_EXECUTE_HANDLER) {
		PostMessage(m_hwnd, WM_CLOSE, 0, 0);
	} 
	return this;
}


//
// Requesting screen updates from the server
//

inline void
ClientConnection::SendFramebufferUpdateRequest(int x, int y, int w, int h, bool incremental)
{
    rfbFramebufferUpdateRequestMsg fur;

    fur.type = rfbFramebufferUpdateRequest;
    fur.incremental = incremental ? 1 : 0;
    fur.x = Swap16IfLE(x);
    fur.y = Swap16IfLE(y);
    fur.w = Swap16IfLE(w);
    fur.h = Swap16IfLE(h);

	log.Print(10, _T("Request %s update\n"), incremental ? _T("incremental") : _T("full"));
    WriteExact((char *)&fur, sz_rfbFramebufferUpdateRequestMsg);
}

inline void ClientConnection::SendIncrementalFramebufferUpdateRequest()
{
    SendFramebufferUpdateRequest(0, 0, m_si.framebufferWidth,
					m_si.framebufferHeight, true);
}

inline void ClientConnection::SendFullFramebufferUpdateRequest()
{
    SendFramebufferUpdateRequest(0, 0, m_si.framebufferWidth,
					m_si.framebufferHeight, false);
}



// A ScreenUpdate message has been received

void ClientConnection::ReadScreenUpdate() {

	rfbFramebufferUpdateMsg sut;
	ReadExact((char *) &sut + 1, sz_rfbFramebufferUpdateMsg-1);
    sut.nRects = Swap16IfLE(sut.nRects);
	if (sut.nRects == 0) return;
	
	// No other threads can use DC
	omni_mutex_lock l(m_bitmapdcMutex);
	
	ObjectSelector b(m_hBitmapDC, m_hBitmap);
	PaletteSelector p(m_hBitmapDC, m_hPalette);
	
	// Find the bounding region of this batch of updates
	HRGN fullregion = NULL;
	
	for (UINT i=0; i < sut.nRects; i++) {
		
		rfbFramebufferUpdateRectHeader surh;
		ReadExact((char *) &surh, sz_rfbFramebufferUpdateRectHeader);
		surh.r.x = Swap16IfLE(surh.r.x);
		surh.r.y = Swap16IfLE(surh.r.y);
		surh.r.w = Swap16IfLE(surh.r.w);
		surh.r.h = Swap16IfLE(surh.r.h);
		surh.encoding = Swap32IfLE(surh.encoding);
		
		switch (surh.encoding) {
		case rfbEncodingRaw:
			ReadRawRect(&surh);
			break;
		case rfbEncodingCopyRect:
			ReadCopyRect(&surh);
			break;
		case rfbEncodingRRE:
			ReadRRERect(&surh);
			break;
		case rfbEncodingCoRRE:
			ReadCoRRERect(&surh);
			break;
		case rfbEncodingHextile:
			ReadHextileRect(&surh);
			break;
		default:
			log.Print(0, _T("Unknown encoding %d - not supported!\n"), surh.encoding);
			break;
		}
		
		RECT rect;
		rect.left   = surh.r.x - m_hScrollPos;
		rect.top    = surh.r.y - m_vScrollPos + m_barheight;
		rect.right  = rect.left + surh.r.w;
		rect.bottom = rect.top  + surh.r.h;
		InvalidateRect(m_hwnd, &rect, FALSE);
	}
}

void ClientConnection::SetDormant(bool newstate)
{
	log.Print(5, _T("%s dormant mode\n"), newstate ? _T("Entering") : _T("Leaving"));
	m_dormant = newstate;
	if (!m_dormant)
		SendIncrementalFramebufferUpdateRequest();
}

// The server has copied some text to the clipboard - put it 
// in the local clipboard too.

void ClientConnection::ReadServerCutText() {
	rfbServerCutTextMsg sctm;
	log.Print(6, _T("Read remote clipboard change\n"));
	ReadExact(((char *) &sctm)+1, sz_rfbServerCutTextMsg -1 );
	int len = Swap32IfLE(sctm.length);
	
	CheckBufferSize(len);
	if (len == 0) {
		m_netbuf[0] = '\0';
	} else {
		ReadString(m_netbuf, len);
	}
#ifndef UNDER_CE
	UpdateLocalClipboard(m_netbuf, len);
#endif
}


void ClientConnection::ReadBell() {
	rfbBellMsg bm;
	ReadExact(((char *) &bm)+1, sz_rfbBellMsg-1);

	#ifdef UNDER_CE
	MessageBeep( MB_OK );
	#else

	if (! ::PlaySound("VNCViewerBell", NULL, 
		SND_APPLICATION | SND_ALIAS | SND_NODEFAULT | SND_ASYNC) ) {
		::Beep(440, 125);
	}
	#endif
	if (m_opts.m_DeiconifyOnBell) {
		if (!IsWindowEnabled(m_hwnd)) {
			SetDormant(false);
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
		}
	}
	log.Print(6, _T("Bell!\n"));
}


// General utilities -------------------------------------------------

// Reads the number of bytes specified into the buffer given

void ClientConnection::ReadExact(char *inbuf, int wanted)
{
	omni_mutex_lock l(m_readMutex);
	// omni_mutex_lock l2(sockMutex);
	int offset = 0;
    log.Print(10, _T("  reading %d bytes\n"), wanted);
	
	while (wanted > 0) {

		int bytes = recv(m_sock, inbuf+offset, wanted, 0);
		if (bytes == 0) RaiseException(VNC_EXC_QUIETCLOSE,0,0,0);
		if (bytes == SOCKET_ERROR) {
			int err = ::GetLastError();
			log.Print(1, _T("Socket error while reading %d\n"), err);
			m_running = false;
			RaiseException(VNC_EXC_QUIETCLOSE,0,0,0);
		}
		wanted -= bytes;
		offset += bytes;

	}
}

// Read the number of bytes and return them zero terminated in the buffer 
void ClientConnection::ReadString(char *buf, int length)
{
	if (length > 0)
		ReadExact(buf, length);
	buf[length] = '\0';
    log.Print(10, _T("Read a %d-byte string\n"), length);
}


// Sends the number of bytes specified from the buffer
void ClientConnection::WriteExact(char *buf, int bytes)
{
	if (bytes == 0) return;
	
	omni_mutex_lock l(m_writeMutex);
	log.Print(10, _T("  writing %d bytes\n"), bytes);

	int i = 0;
    int j;

    while (i < bytes) {

		j = send(m_sock, buf+i, bytes-i, 0);
		if (j == SOCKET_ERROR || j==0) {
			int err = ::GetLastError();
			log.Print(1, _T("Socket error %d\n"), err);
			m_running = false;

			RaiseException(VNC_EXC_QUIETCLOSE,0,0,0);
		}
		i += j;
    }
}

// Makes sure netbuf is at least as big as the specified size.
// Note that netbuf itself may change as a result of this call.
// Throws an exception on failure.
void ClientConnection::CheckBufferSize(int bufsize)
{
	if (m_netbufsize > bufsize) return;

	omni_mutex_lock l(m_bufferMutex);

	char *newbuf = new char[bufsize+256];;
	if (newbuf == NULL) {
		RaiseException(VNC_EXC_MEMORY,0,0,0);;
	}

	// Only if we're successful...

	if (m_netbuf != NULL)
		delete [] m_netbuf;
	m_netbuf = newbuf;
	m_netbufsize=bufsize + 256;
	log.Print(4, _T("bufsize expanded to %d\n"), m_netbufsize);
}
