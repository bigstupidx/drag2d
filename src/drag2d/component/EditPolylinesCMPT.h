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

#ifndef D2D_EDIT_POLYLINES_CMPT_H
#define D2D_EDIT_POLYLINES_CMPT_H

#include "AbstractEditCMPT.h"

namespace d2d
{
	class MultiShapesImpl;
	class PropertySettingPanel;

	class EditPolylinesCMPT : public AbstractEditCMPT
	{
	public:
		EditPolylinesCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl,
			PropertySettingPanel* propertyPanel);

		virtual void updateControlValue();

		float getSimplifyThreshold() const;

	protected:
		virtual wxSizer* initLayout();

	private:
		wxSizer* initSimplifyPanel();
		wxSizer* initSmoothPanel();
		wxSizer* initEditPanel();

		void onSimplifyThresholdChanged(wxSpinEvent& event);
		void onUpdateFromSimplified(wxCommandEvent& event);

		void onMergeTwoChain(wxCommandEvent& event);
		void onTranslate(wxCommandEvent& event);

	private:
		MultiShapesImpl* m_shapesImpl;

		wxSpinCtrl* m_simplifySpin;

		wxButton* m_btnMerge;

	}; // EditPolylinesCMPT
}

#endif // D2D_EDIT_POLYLINES_CMPT_H
