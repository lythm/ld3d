#include "stdafx.h"
#include "InspectorProperty_String.h"
#include "resource.h"


CInspectorProperty_String::CInspectorProperty_String(CString name, CString value, void* pUserData) 
				: CInspectorProperty_Simple(name, pUserData, IDD_INSPECTOR_PROPERTY_STRING)
{
	m_value = value;
}


CInspectorProperty_String::~CInspectorProperty_String(void)
{
}


BOOL CInspectorProperty_String::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());
	SetDlgItemText(IDC_VALUE, m_value);

	m_edit.SetReadOnly(GetReadOnly());
	return TRUE;

}
BEGIN_MESSAGE_MAP(CInspectorProperty_String, CInspectorProperty_Simple)
	ON_EN_CHANGE(IDC_VALUE, &CInspectorProperty_String::OnEnChangeValue)
	ON_EN_KILLFOCUS(IDC_VALUE, &CInspectorProperty_String::OnEnKillfocusValue)
END_MESSAGE_MAP()


void CInspectorProperty_String::OnEnChangeValue()
{
	
}
CString CInspectorProperty_String::GetValue() const
{
	CString str;
	GetDlgItemText(IDC_VALUE, str);
	return str;
}
void CInspectorProperty_String::SetValue(CString v)
{
	SetDlgItemText(IDC_VALUE, v);
}

void CInspectorProperty_String::OnEnKillfocusValue()
{
	OnValueChanged();
}
void CInspectorProperty_String::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_edit);
}
