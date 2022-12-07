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


// VNCOptions.cpp: implementation of the VNCOptions class.

#include "stdhdrs.h"
#include "vncviewer.h"
#include "VNCOptions.h"
#include "Exception.h"

VNCOptions::VNCOptions()
{
	for (int i = rfbEncodingRaw; i<= LASTENCODING; i++)
		m_UseEnc[i] = true;
	
	m_ViewOnly = false;
	m_Use8Bit = false;
	m_PreferredEncoding = rfbEncodingHextile;
	m_SwapMouse = false;
	m_Emul3Buttons = false;  // not implemented yet
	m_Shared = false;
	m_DeiconifyOnBell = false;
	m_host[0] = '\0';
	m_port = -1;
	
	m_kbdname[0] = '\0';
	m_kbdSpecified = false;
	
	m_logLevel = 0;
	m_logToConsole = false;
	m_logToFile = false;
	
	m_delay=0;
	m_connectionSpecified = false;
	m_listening = false;
	m_restricted = false;
}

VNCOptions::~VNCOptions()
{
	
}

inline bool SwitchMatch(LPCTSTR arg, LPCTSTR swtch) {
	return (arg[0] == '-' || arg[0] == '/') &&
		(_tcsicmp(&arg[1], swtch) == 0);
}

static void ArgError(LPTSTR msg) {
    MessageBox(NULL,  msg, _T("Argument error"),MB_OK | MB_TOPMOST | MB_ICONSTOP);
}

void VNCOptions::SetFromCommandLine(LPTSTR szCmdLine) {
	// We assume no quoting here.
	// Copy the command line - we don't know what might happen to the original
	int cmdlinelen = _tcslen(szCmdLine);
	if (cmdlinelen == 0) return;
	
	TCHAR *cmd = new TCHAR[cmdlinelen + 1];
	_tcscpy(cmd, szCmdLine);
	
	// count the number of spaces
	int nspaces = 0;
	TCHAR *p = cmd;
	TCHAR *pos = cmd;
	while ( ( pos = _tcschr(p, ' ') ) != NULL ) {
		nspaces ++;
		p = pos + 1;
	}
	
	// Create the array to hold pointers to each bit of string
	TCHAR **args = new LPTSTR[nspaces + 1];
	
	// replace spaces with nulls and
	// create an array of TCHAR*'s which points to start of each bit.
	p = cmd; 
	pos = cmd;
	int i = 0;
	args[i++] = cmd;
	while ( ( pos = _tcschr(p, ' ') ) != NULL ) {
		*pos = '\0';
		p = pos + 1;
		args[i++] = p;
	}
	bool hostGiven = false, portGiven = false;
	// take in order.
	for (int j = 0; j < i; j++) {
		if ( SwitchMatch(args[j], _T("help")) ||
			SwitchMatch(args[j], _T("?")) ||
			SwitchMatch(args[j], _T("h"))) {
			ShowUsage();
			PostQuitMessage(1);
		} else if ( SwitchMatch(args[j], _T("listen"))) {
			m_listening = true;
		} else if ( SwitchMatch(args[j], _T("restricted"))) {
			m_restricted = true;
		} else if ( SwitchMatch(args[j], _T("viewonly"))) {
			m_ViewOnly = true;
		} else if ( SwitchMatch(args[j], _T("8bit"))) {
			m_Use8Bit = true;
		} else if ( SwitchMatch(args[j], _T("shared"))) {
			m_Shared = true;
		} else if ( SwitchMatch(args[j], _T("swapmouse"))) {
			m_SwapMouse = true;
		} else if ( SwitchMatch(args[j], _T("belldeiconify") )) {
			m_DeiconifyOnBell = true;
		} else if ( SwitchMatch(args[j], _T("delay") )) {
			if (++j == i) {
				ArgError(_T("No delay specified"));
				continue;
			}
			if (_stscanf(args[j], _T("%d"), &m_delay) != 1) {
				ArgError(_T("Invalid delay specified"));
				continue;
			}
			
		} else if ( SwitchMatch(args[j], _T("loglevel") )) {
			if (++j == i) {
				ArgError(_T("No loglevel specified"));
				continue;
			}
			if (_stscanf(args[j], _T("%d"), &m_logLevel) != 1) {
				ArgError(_T("Invalid loglevel specified"));
				continue;
			}
			
		} else if ( SwitchMatch(args[j], _T("console") )) {
			m_logToConsole = true;
		} else if ( SwitchMatch(args[j], _T("logfile") )) {
			if (++j == i) {
				ArgError(_T("No logfile specified"));
				continue;
			}
			if (_stscanf(args[j], _T("%s"), &m_logFilename) != 1) {
				ArgError(_T("Invalid logfile specified"));
				continue;
			} else {
				m_logToFile = true;
			}
		} else {
			TCHAR phost[256];
			if (!ParseDisplay(args[j], phost, 255, &m_port)) {
				ShowUsage(_T("Invalid VNC server specified."));
				PostQuitMessage(1);
			} else {
				_tcscpy(m_host, phost);
				m_connectionSpecified = true;
			}
		}
	}       
	
	// tidy up
	delete [] cmd;
	delete [] args;
}

void VNCOptions::ShowUsage(LPTSTR info) {
    TCHAR msg[1024];
    TCHAR *tmpinf = _T("");
    if (info != NULL) 
        tmpinf = info;
    _stprintf(msg, 
#ifdef UNDER_CE
        _T("%s\n\rUsage:\n\r  vncviewer [/8bit] [/swapmouse] [/shared] [/belldeiconify] [server:display]"), 
#else
        _T("%s\n\rUsage:\n\r  vncviewer [/8bit] [/swapmouse] [/shared] [/belldeiconify] [/listen] [server:display]"), 
#endif
        tmpinf);
    MessageBox(NULL,  msg, _T("VNC error"), MB_OK | MB_ICONSTOP | MB_TOPMOST);
}

// The dialog box allows you to change the session-specific parameters
int VNCOptions::DoDialog(bool running)
{
	m_running = running;
	return DialogBoxParam(pApp->m_instance, MAKEINTRESOURCE(IDD_OPTIONDIALOG), 
		NULL, (DLGPROC) OptDlgProc, (LONG) this);
}

BOOL CALLBACK VNCOptions::OptDlgProc(  HWND hwnd,  UINT uMsg,  
									 WPARAM wParam, LPARAM lParam ) {
	// This is a static method, so we don't know which instantiation we're 
	// dealing with. But we can get a pseudo-this from the parameter to 
	// WM_INITDIALOG, which we therafter store with the window and retrieve
	// as follows:
	VNCOptions *_this = (VNCOptions *) GetWindowLong(hwnd, GWL_USERDATA);
	
	switch (uMsg) {
		
	case WM_INITDIALOG:
		{
			SetWindowLong(hwnd, GWL_USERDATA, lParam);
			_this = (VNCOptions *) lParam;
			// Initialise the controls
			for (int i = rfbEncodingRaw; i <= LASTENCODING; i++) {
				HWND hPref = GetDlgItem(hwnd, IDC_RAWRADIO + (i-rfbEncodingRaw));
				SendMessage(hPref, BM_SETCHECK, 
					(i== _this->m_PreferredEncoding), 0);
				EnableWindow(hPref, _this->m_UseEnc[i]);
			}
			
			HWND hCopyRect = GetDlgItem(hwnd, ID_SESSION_SET_CRECT);
			SendMessage(hCopyRect, BM_SETCHECK, _this->m_UseEnc[rfbEncodingCopyRect], 0);
			
			HWND hSwap = GetDlgItem(hwnd, ID_SESSION_SWAPMOUSE);
			SendMessage(hSwap, BM_SETCHECK, _this->m_SwapMouse, 0);
			
			HWND hDeiconify = GetDlgItem(hwnd, IDC_BELLDEICONIFY);
			SendMessage(hDeiconify, BM_SETCHECK, _this->m_DeiconifyOnBell, 0);
			
			
			HWND h8bit = GetDlgItem(hwnd, IDC_8BITCHECK);
			SendMessage(h8bit, BM_SETCHECK, _this->m_Use8Bit, 0);
			
			HWND hShared = GetDlgItem(hwnd, IDC_SHARED);
			SendMessage(hShared, BM_SETCHECK, _this->m_Shared, 0);
			EnableWindow(hShared, !_this->m_running);
			
			HWND hViewOnly = GetDlgItem(hwnd, IDC_VIEWONLY);
			SendMessage(hViewOnly, BM_SETCHECK, _this->m_ViewOnly, 0);
			
			CentreWindow(hwnd);
			
			return TRUE;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			{
				for (int i = rfbEncodingRaw; i <= LASTENCODING; i++) {
					HWND hPref = GetDlgItem(hwnd, IDC_RAWRADIO+i-rfbEncodingRaw);
					if (SendMessage(hPref, BM_GETCHECK, 0, 0) == BST_CHECKED)
						_this->m_PreferredEncoding = i;
				}
				
				HWND hCopyRect = GetDlgItem(hwnd, ID_SESSION_SET_CRECT);
				_this->m_UseEnc[rfbEncodingCopyRect] =
					(SendMessage(hCopyRect, BM_GETCHECK, 0, 0) == BST_CHECKED);
				
				HWND hSwap = GetDlgItem(hwnd, ID_SESSION_SWAPMOUSE);
				_this->m_SwapMouse =
					(SendMessage(hSwap, BM_GETCHECK, 0, 0) == BST_CHECKED);
				
				HWND hDeiconify = GetDlgItem(hwnd, IDC_BELLDEICONIFY);
				_this->m_DeiconifyOnBell =
					(SendMessage(hDeiconify, BM_GETCHECK, 0, 0) == BST_CHECKED);
				
				HWND h8bit = GetDlgItem(hwnd, IDC_8BITCHECK);
				_this->m_Use8Bit =
					(SendMessage(h8bit, BM_GETCHECK, 0, 0) == BST_CHECKED);
				
				HWND hShared = GetDlgItem(hwnd, IDC_SHARED);
				_this->m_Shared =
					(SendMessage(hShared, BM_GETCHECK, 0, 0) == BST_CHECKED);
				
				HWND hViewOnly = GetDlgItem(hwnd, IDC_VIEWONLY);
				_this->m_ViewOnly = 
					(SendMessage(hViewOnly, BM_GETCHECK, 0, 0) == BST_CHECKED);
				
				EndDialog(hwnd, TRUE);
				
				return TRUE;
			}
		case IDCANCEL:
			EndDialog(hwnd, FALSE);
			return TRUE;
		}
		break;
        case WM_DESTROY:
			EndDialog(hwnd, FALSE);
			return TRUE;
	}
	return 0;
}

