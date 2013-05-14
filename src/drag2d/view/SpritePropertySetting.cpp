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

#include "SpritePropertySetting.h"
#include "PropertySettingPanel.h"

#include "dataset/ISprite.h"
#include "view/EditPanel.h"

using namespace d2d;

SpritePropertySetting::SpritePropertySetting(EditPanel* editPanel, ISprite* sprite)
	: IPropertySetting(editPanel, wxT("ISprite"))
	, m_sprite(sprite)
{
}

void SpritePropertySetting::updatePanel(PropertySettingPanel* panel)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) == m_type)
	{
 		pg->GetProperty(wxT("X"))->SetValue(m_sprite->getPosition().x);
 		pg->GetProperty(wxT("Y"))->SetValue(m_sprite->getPosition().y);
 		pg->GetProperty(wxT("�Ƕ�"))->SetValue(m_sprite->getAngle());
 		pg->GetProperty(wxT("����"))->SetValue(m_sprite->getScale());
 
 		bool xMirror, yMirror;
 		m_sprite->getMirror(xMirror, yMirror);
 		pg->GetProperty(wxT("ˮƽ����"))->SetValue(xMirror);
 		pg->GetProperty(wxT("��ֱ����"))->SetValue(yMirror);
	}
	else
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_type));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_sprite->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_sprite->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("�Ƕ�"), wxPG_LABEL, m_sprite->getAngle()));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("����"), wxPG_LABEL, m_sprite->getScale()));
		pg->SetPropertyAttribute(wxT("����"), wxPG_ATTR_UNITS, wxT("��"));
		pg->SetPropertyAttribute(wxT("����"), "Precision", 2);

		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("ˮƽ����"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("��ֱ����"), wxPG_LABEL, yMirror));
	}
}

void SpritePropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("X"))
		m_sprite->setTransform(Vector(wxANY_AS(value, float), m_sprite->getPosition().y), m_sprite->getAngle());
	else if (name == wxT("Y"))
		m_sprite->setTransform(Vector(m_sprite->getPosition().x, wxANY_AS(value, float)), m_sprite->getAngle());
	else if (name == wxT("�Ƕ�"))
		m_sprite->setTransform(m_sprite->getPosition(), wxANY_AS(value, float));
	else if (name == wxT("����"))
		m_sprite->setScale(wxANY_AS(value, float));
	else if (name == wxT("ˮƽ����"))
	{
		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		m_sprite->setMirror(wxANY_AS(value, bool), yMirror);
	}
	else if (name == wxT("��ֱ����"))
	{
		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		m_sprite->setMirror(xMirror, wxANY_AS(value, bool));
	}

	m_editPanel->Refresh();
}

void SpritePropertySetting::updatePropertyGrid(PropertySettingPanel* panel)
{
	updatePanel(panel);
}

void SpritePropertySetting::enablePropertyGrid(PropertySettingPanel* panel, bool bEnable)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) != m_type)
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_type));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_sprite->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_sprite->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("�Ƕ�"), wxPG_LABEL, m_sprite->getAngle()));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("����"), wxPG_LABEL, m_sprite->getScale()));
		pg->SetPropertyAttribute(wxT("����"), wxPG_ATTR_UNITS, wxT("��"));
		pg->SetPropertyAttribute(wxT("����"), "Precision", 2);

		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("ˮƽ����"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("��ֱ����"), wxPG_LABEL, yMirror));
	}

	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("X"))->Enable(bEnable);
	pg->GetProperty(wxT("Y"))->Enable(bEnable);
	pg->GetProperty(wxT("�Ƕ�"))->Enable(bEnable);
	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("ˮƽ����"))->Enable(bEnable);
	pg->GetProperty(wxT("��ֱ����"))->Enable(bEnable);
}
