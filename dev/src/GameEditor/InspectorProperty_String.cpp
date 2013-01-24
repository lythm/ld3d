#include "stdafx.h"
#include "InspectorProperty_String.h"
#include "resource.h"


CInspectorProperty_String::CInspectorProperty_String(CString name) : CInspectorProperty_Simple(name, IDD_INSPECTOR_PROPERTY_STRING)
{
	m_value = L"";
}


CInspectorProperty_String::~CInspectorProperty_String(void)
{
}


BOOL CInspectorProperty_String::OnInitDialog()
{
	CInspectorProperty::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());
	SetDlgItemText(IDC_VALUE, m_value);
	return TRUE;

}
BEGIN_MESSAGE_MAP(CInspectorProperty_String, CInspectorProperty_Simple)
	ON_EN_CHANGE(IDC_VALUE, &CInspectorProperty_String::OnEnChangeValue)
END_MESSAGE_MAP()


void CInspectorProperty_String::OnEnChangeValue()
{
	GetDlgItemText(IDC_VALUE, m_value);
}
