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

// Raw Encoding
//
// The bits of the ClientConnection object to do with Raw.

#include "stdhdrs.h"
#include "vncviewer.h"
#include "ClientConnection.h"

void ClientConnection::ReadRawRect(rfbFramebufferUpdateRectHeader *pfburh) {

	UINT numpixels = pfburh->r.w * pfburh->r.h;
    // this assumes at least one byte per pixel. Naughty.
	UINT numbytes = numpixels * m_minPixelBytes;
	// Read in the whole thing
    CheckBufferSize(numbytes);
	ReadExact(m_netbuf, numbytes);

	SETUP_COLOR_SHORTCUTS;

	// This big switch is untidy but fast
	switch (m_myFormat.bitsPerPixel) {
	case 8:
		SETPIXELS(8, pfburh->r.x, pfburh->r.y, pfburh->r.w, pfburh->r.h)
		break;
	case 16:
		SETPIXELS(16, pfburh->r.x, pfburh->r.y, pfburh->r.w, pfburh->r.h)
		break;
	case 24:
	case 32:
		SETPIXELS(32, pfburh->r.x, pfburh->r.y, pfburh->r.w, pfburh->r.h)            
		break;
	default:
		log.Print(0, _T("Invalid number of bits per pixel: %d\n"), m_myFormat.bitsPerPixel);
		return;
	}
	
}
