/*
* Copyright (c) 2012-2013 XZRUNNER http://runnersoft.net
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

#include "PasteSymbolRandomCMPT.h"

#include "operator/PasteSymbolRandomOP.h"
#include "widgets/PasteSymbolRandomWidget.h"

using namespace d2d;

PasteSymbolRandomCMPT::PasteSymbolRandomCMPT(wxWindow* parent, const wxString& name, 
											 EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
											 LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_randomWidget = new PasteSymbolRandomWidget(this, libraryPanel);
	m_editOP = new PasteSymbolRandomOP(editPanel, spritesImpl, libraryPanel, m_randomWidget);
}

wxSizer* PasteSymbolRandomCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(m_randomWidget);
	return topSizer;
}
