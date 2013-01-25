#include "stdafx.h"
#include "InspectorProperty_Float.h"

#include "resource.h"



CInspectorProperty_Float::CInspectorProperty_Float(CString name, float value, void* pUserData) 
	: CInspectorProperty_Simple(name, pUserData, IDD_INSPECTOR_PROPERTY_FLOAT)
{
	m_initValue = value;
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
	m_value.SetValue(m_initValue);
	m_value.SetReadOnly(GetReadOnly());
	return TRUE;
}


void CInspectorProperty_Float::OnEnKillfocusValue()
{
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