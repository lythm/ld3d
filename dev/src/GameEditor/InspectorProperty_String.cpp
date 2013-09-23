#include "stdafx.h"
#include "InspectorProperty_String.h"
#include "resource.h"


CInspectorProperty_String::CInspectorProperty_String(CString name, ld3d::Property* pProp, void* pUserData) 
				: CInspectorProperty_Simple(name, pProp, pUserData, IDD_INSPECTOR_PROPERTY_STRING)
{

}


CInspectorProperty_String::~CInspectorProperty_String(void)
{
}


BOOL CInspectorProperty_String::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());
	

	ld3d::Property_T<std::wstring> * pProp = (ld3d::Property_T<std::wstring>*)GetProperty();
	SetValue(pProp->Get().c_str());

	m_edit.SetReadOnly(pProp->IsReadOnly());
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
	ld3d::Property_T<std::wstring> * pProp = (ld3d::Property_T<std::wstring>*)GetProperty();
	pProp->Set(GetValue().GetString());

	OnValueChanged();
}
void CInspectorProperty_String::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_edit);
}
