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
#include "VNCviewerAppCE.h"

VNCviewerAppCE::VNCviewerAppCE(HINSTANCE hInstance, LPTSTR szCmdLine) :
	VNCviewerApp(hInstance, szCmdLine) 
{
	INITCOMMONCONTROLSEX icce;
	icce.dwSize = sizeof(icce);
	icce.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icce);
}

	// These should maintain a list of connections.

void VNCviewerAppCE::NewConnection() {
	ClientConnection *pcc = new ClientConnection(this);
	__try {
		pcc->Run();
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		delete pcc;
	} 
}

void VNCviewerAppCE::NewConnection(TCHAR *host, int port) {
	ClientConnection *pcc = new ClientConnection(this, host,port);
	__try {
		pcc->Run();
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		delete pcc;
	} 
}

void VNCviewerAppCE::NewConnection(SOCKET sock) {
	ClientConnection *pcc = new ClientConnection(this, sock);
	__try {
		pcc->Run();
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		delete pcc;
	} 
}

VNCviewerAppCE::~VNCviewerAppCE()  
{
}