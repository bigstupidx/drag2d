/*
* Copyright (c) 2012-2013 Guang Zhu http://runnersoft.net
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef D2D_PASTE_SYMBOL_CAPTURE_OP_H
#define D2D_PASTE_SYMBOL_CAPTURE_OP_H

#include "PasteSymbolOP.h"

#include "component/PasteSymbolOffsetCMPT.h"

namespace d2d
{
	class PasteSymbolCaptureOP;
	class MultiSpritesImpl;
	class LibraryPanel;

	class PasteSymbolCaptureOP : public PasteSymbolOP
	{
	public:
		PasteSymbolCaptureOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel, PasteSymbolOffsetCMPT<PasteSymbolCaptureOP>* cmpt);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseMove(int x, int y);

		virtual bool clear();

	private:
		PasteSymbolOffsetCMPT<PasteSymbolCaptureOP>* m_cmpt;

		bool m_bCaptured;
		Vector m_lastPos;

	}; // PasteSymbolCaptureOP
}

#endif // D2D_PASTE_SYMBOL_CAPTURE_OP_H
