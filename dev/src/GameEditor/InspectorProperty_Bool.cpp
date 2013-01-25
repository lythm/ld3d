#include "stdafx.h"
#include "InspectorProperty_Bool.h"
#include "resource.h"


CInspectorProperty_Bool::CInspectorProperty_Bool(CString name, bool value, void* pUserData ) 
			: CInspectorProperty_Simple(name, pUserData, IDD_INSPECTOR_PROPERTY_BOOL)
{
	m_value = value;
}


CInspectorProperty_Bool::~CInspectorProperty_Bool(void)
{
}
void CInspectorProperty_Bool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_valueButton);
}


BOOL CInspectorProperty_Bool::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());
	m_valueButton.SetCheck(m_value ? BST_CHECKED : BST_UNCHECKED);

	m_valueButton.EnableWindow(GetReadOnly() == false);

	return TRUE;
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Bool, CInspectorProperty_Simple)
	ON_BN_CLICKED(IDC_VALUE, &CInspectorProperty_Bool::OnBnClickedValue)
END_MESSAGE_MAP()


void CInspectorProperty_Bool::OnBnClickedValue()
{
	OnValueChanged();
}
bool CInspectorProperty_Bool::GetValue()
{
	return m_valueButton.GetCheck() == BST_CHECKED;
}
void CInspectorProperty_Bool::SetValue(bool v)
{
	m_valueButton.SetCheck(v ? BST_CHECKED : BST_UNCHECKED);
}