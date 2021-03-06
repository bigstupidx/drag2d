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

#include "VerticalImageList.h"
#include "ListItem.h"

#include "dataset/Bitmap.h"
#include "widgets/DragTargetNull.h"

using namespace d2d;

VerticalImageList::VerticalImageList(wxWindow* parent, const wxString& name/* = wxEmptyString*/,
									 bool draggable /*= true*/)
	: wxVListBox(parent)
	, m_name(name)
{
	SetBackgroundColour(wxColour(229, 229, 229));

	Connect(GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(VerticalImageList::onListSelected));
	Connect(GetId(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(VerticalImageList::onListDoubleClicked));

	if (draggable)
	{
		SetDropTarget(new DragTargetNull);
		Connect(GetId(), wxEVT_MOTION, wxMouseEventHandler(VerticalImageList::onDragInit));
	}
}

VerticalImageList::~VerticalImageList()
{
	clear();
}

void VerticalImageList::traverse(IVisitor& visitor) const
{
	std::vector<ListItem*>::const_iterator itr = m_items.begin();
	for ( ; itr != m_items.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void VerticalImageList::clear()
{
//	for_each(m_items.begin(), m_items.end(), DeletePointerFunctor<ListItem>());
	m_items.clear();
	SetItemCount(0);
	Refresh();
}

void VerticalImageList::insert(ListItem* item)
{
	m_items.push_back(item);
	SetItemCount(m_items.size());
	SetSelection(m_items.size() - 1);
	Refresh();
}

void VerticalImageList::remove()
{
	int index = GetSelection();
	if (index >= 0 && index < m_items.size())
	{
//		delete m_items[index];
		m_items.erase(m_items.begin() + index);
		onListSelected(wxCommandEvent(GetSelection()));
		SetItemCount(m_items.size());
		Refresh();
	}
}

void VerticalImageList::swap(int i0, int i1)
{
	if (i0 < 0 || i0 >= m_items.size() ||
		i1 < 0 || i1 >= m_items.size())
		return;

	ListItem* tmp = m_items[i0];
	m_items[i0] = m_items[i1];
	m_items[i1] = tmp;

	Refresh();
}

void VerticalImageList::OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const
{
	int y = rect.y + SPACE_UP;

	const Bitmap* bmp = m_items[n]->getBitmap();
	if (bmp)
	{
		const wxBitmap* wxBmp = bmp->getBitmap();
		int x = wxBmp->GetWidth() > rect.width ? 0 : (rect.width - wxBmp->GetWidth()) * 0.5f;
		dc.DrawBitmap(*wxBmp, x, y);
		y += wxBmp->GetHeight();
	}

	wxString name = m_items[n]->getName();
	wxSize size = dc.GetTextExtent(name);
	dc.DrawText(name, rect.x + rect.width * 0.5f - size.GetWidth() * 0.5f, y + SPACE_UP);
}

// void VerticalImageList::OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n) const
// {
//   	dc.SetPen(*wxRED_PEN);
//   	dc.DrawRectangle(rect);
// }

void VerticalImageList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const
{
	dc.SetPen(wxPen(wxColour(0, 0, 0), 3));
	dc.DrawLine(rect.GetLeftBottom(), rect.GetRightBottom());
}

wxCoord VerticalImageList::OnMeasureItem(size_t n) const
{
	const Bitmap* bmp = m_items[n]->getBitmap();
	if (bmp) 
		return bmp->getBitmap()->GetHeight() + SPACE_UP + SPACE_DOWN;
	else 
		return SPACE_UP + SPACE_DOWN;
}

void VerticalImageList::onDragInit(wxMouseEvent& event)
{
	if (event.Dragging())
	{
		wxTextDataObject tdo(m_name + "," + wxString::FromDouble(GetSelection()));
		wxDropSource ds(tdo);
		ds.DoDragDrop(wxDrag_CopyOnly);
	}
}
