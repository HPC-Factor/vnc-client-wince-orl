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


#include "stdhdrs.h"
#include "vncviewer.h"
#include "Exception.h"
#include "omnithreadce.h"
#include "VNCviewerAppCE.h"

// All logging is done via the log object
Log log;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, int iCmdShow)
{
	// We shouldn't need to do this here, it should be initialised as a static.
	// Bug in the CE compiler, I think.
	omni_thread::init_t omni_thread_init;

	// The state of the application as a whole is contained in the one app object
	VNCviewerAppCE app(hInstance, szCmdLine);

	// Start a new connection if specified on command line
	// or if not in listening mode
	
	if (app.m_options.m_connectionSpecified) {
		app.NewConnection(app.m_options.m_host, app.m_options.m_port);
	} else if (!app.m_options.m_listening) {
		app.NewConnection();
	}

	MSG msg;
	
	__try {
		while ( GetMessage(&msg, NULL, 0,0) ) {
			TranslateMessage(&msg);  // convert key ups and downs to chars
			DispatchMessage(&msg);
		} 
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		// This is probably too general! Catch all exceptions and exit quietly.
	}
	
	// Clean up winsock
	WSACleanup();

    log.Print(3, _T("Exiting\n"));

	return msg.wParam;
}


// Move the given window to the centre of the screen
// and bring it to the top.
void CentreWindow(HWND hwnd)
{
	RECT winrect, workrect;
	
	// Find how large the desktop work area is
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workrect, 0);
	int workwidth = workrect.right -  workrect.left;
	int workheight = workrect.bottom - workrect.top;
	
	// And how big the window is
	GetWindowRect(hwnd, &winrect);
	int winwidth = winrect.right - winrect.left;
	int winheight = winrect.bottom - winrect.top;
	// Make sure it's not bigger than the work area
	winwidth = min(winwidth, workwidth);
	winheight = min(winheight, workheight);

	// Now centre it
	SetWindowPos(hwnd, 
		HWND_TOP,
		workrect.left + (workwidth-winwidth) / 2,
		workrect.top + (workheight-winheight) / 2,
		winwidth, winheight, 
		SWP_SHOWWINDOW);
	SetForegroundWindow(hwnd);
}

// Convert "host:display" into host and port
// Returns true if valid format, false if not.
// Takes initial string, addresses of results and size of host buffer in wchars.
// If the display info passed in is longer than the size of the host buffer, it
// is assumed to be invalid, so false is returned.
bool ParseDisplay(LPTSTR display, LPTSTR phost, int hostlen, int *pport) 
{
    int tmpport;
    if (hostlen < (int) _tcslen(display))
        return false;
    TCHAR *colonpos = _tcschr( display, L':' );
    if (colonpos == NULL) 
        return false;
    _tcsncpy(phost, display, colonpos-display);
    phost[colonpos-display] = L'\0';
    if (_stscanf(colonpos+1, TEXT("%d"), &tmpport) != 1) 
        return false;
    if (tmpport < 100)
        tmpport += RFB_PORT_OFFSET;
    *pport = tmpport;
    return true;
}


