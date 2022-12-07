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



#pragma once

#define LASTENCODING rfbEncodingHextile

class VNCOptions  
{
public:
	VNCOptions();
	virtual ~VNCOptions();

	// process options
	bool	m_listening;
	bool	m_connectionSpecified;
	bool	m_restricted;

	// default connection options - can be set through Dialog
	bool	m_ViewOnly;
	bool	m_Use8Bit;
	int		m_PreferredEncoding;
	bool	m_SwapMouse;
	bool    m_Emul3Buttons;  // not implemented yet
	bool	m_Shared;
	bool	m_DeiconifyOnBell;

	// Keyboard can be specified on command line as 8-digit hex
	TCHAR	m_kbdname[9];
	bool	m_kbdSpecified;

	// Connection options we don't do through the dialog
	// Which encodings do we allow?
	bool	m_UseEnc[LASTENCODING+1];

	TCHAR   m_host[256];
	int     m_port;

    // Logging
    int     m_logLevel;
    bool    m_logToFile, m_logToConsole;
    TCHAR   m_logFilename[1024];
    
	// for debugging purposes
	int m_delay;

	int DoDialog(bool running = false);
	void SetFromCommandLine(LPTSTR szCmdLine);


	static BOOL CALLBACK OptDlgProc(  HWND hwndDlg,  UINT uMsg, 
		WPARAM wParam, LPARAM lParam );

private:
    void ShowUsage(LPTSTR info = NULL);

	// Just for temporary use
	bool m_running;

};

