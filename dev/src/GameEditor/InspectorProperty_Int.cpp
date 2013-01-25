#include "stdafx.h"
#include "InspectorProperty_Int.h"
#include "resource.h"
#include "editor_utils.h"
#include <locale>


CInspectorProperty_Int::CInspectorProperty_Int(CString name, int value, void* pUserData) : CInspectorProperty_Simple(name, pUserData, IDD_INSPECTOR_PROPERTY_INT)
{
	m_oriValue = value;
}


CInspectorProperty_Int::~CInspectorProperty_Int(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Int, CInspectorProperty_Simple)
	ON_EN_CHANGE(IDC_VALUE, &CInspectorProperty_Int::OnEnChangeValue)
	ON_EN_UPDATE(IDC_VALUE, &CInspectorProperty_Int::OnEnUpdateValue)
	
	ON_EN_KILLFOCUS(IDC_VALUE, &CInspectorProperty_Int::OnEnKillfocusValue)
END_MESSAGE_MAP()


BOOL CInspectorProperty_Int::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();
	SetDlgItemText(IDC_NAME, GetName());
	m_valueEdit.SetValue(m_oriValue);
	m_valueEdit.SetReadOnly(GetReadOnly());
	return TRUE;
}

void CInspectorProperty_Int::OnEnChangeValue()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CInspectorProperty::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

		
	// TODO:  在此添加控件通知处理程序代码
}
int	CInspectorProperty_Int::GetValue() const
{
	return m_valueEdit.GetValue();
}
void CInspectorProperty_Int::SetValue(int v)
{
	m_valueEdit.SetValue(v);
}




void CInspectorProperty_Int::OnEnUpdateValue()
{
}

void CInspectorProperty_Int::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_valueEdit);
}



void CInspectorProperty_Int::OnEnKillfocusValue()
{
	OnValueChanged();
}
