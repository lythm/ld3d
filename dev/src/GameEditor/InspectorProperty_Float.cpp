#include "stdafx.h"
#include "InspectorProperty_Float.h"

#include "resource.h"



CInspectorProperty_Float::CInspectorProperty_Float(CString name, ld3d::Property* pProp,  void* pUserData) 
	: CInspectorProperty_Simple(name, pProp, pUserData, IDD_INSPECTOR_PROPERTY_FLOAT)
{
}


CInspectorProperty_Float::~CInspectorProperty_Float(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Float, CInspectorProperty_Simple)

	ON_EN_KILLFOCUS(IDC_VALUE, &CInspectorProperty_Float::OnEnKillfocusValue)
END_MESSAGE_MAP()


void CInspectorProperty_Float::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_VALUE, m_value);
	DDX_Control(pDX, IDC_VALUE, m_value);
}


BOOL CInspectorProperty_Float::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());
	ld3d::Property_T<float> * pProp = (ld3d::Property_T<float>*)GetProperty();
	SetValue(pProp->Get());
	m_value.SetReadOnly(pProp->IsReadOnly());

	pProp->on_property_changed = [=](ld3d::Property* prop)
	{
		ld3d::Property_T<float> * pProp = (ld3d::Property_T<float>*)prop;
		SetValue(pProp->Get());
	};
	return TRUE;
}


void CInspectorProperty_Float::OnEnKillfocusValue()
{
	ld3d::Property_T<float> * pProp = (ld3d::Property_T<float>*)GetProperty();

	pProp->Set(GetValue());

	OnValueChanged();
}
float CInspectorProperty_Float::GetValue()
{
	return m_value.GetValue();
}
void CInspectorProperty_Float::SetValue(float v)
{
	m_value.SetValue(v);
}