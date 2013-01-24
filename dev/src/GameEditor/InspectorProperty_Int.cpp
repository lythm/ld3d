#include "stdafx.h"
#include "InspectorProperty_Int.h"
#include "resource.h"
#include "editor_utils.h"
#include <locale>


CInspectorProperty_Int::CInspectorProperty_Int(CString name) : CInspectorProperty_Simple(name, IDD_INSPECTOR_PROPERTY_INT)
{
	m_value = 0;
}


CInspectorProperty_Int::~CInspectorProperty_Int(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Int, CInspectorProperty_Simple)
	ON_EN_CHANGE(IDC_VALUE, &CInspectorProperty_Int::OnEnChangeValue)
	ON_EN_UPDATE(IDC_VALUE, &CInspectorProperty_Int::OnEnUpdateValue)
	
END_MESSAGE_MAP()




BOOL CInspectorProperty_Int::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();
	SetDlgItemText(IDC_NAME, GetName());
	SetDlgItemInt(IDC_VALUE, m_value);
	return TRUE;
}

void CInspectorProperty_Int::ProcessInput()
{

}

void CInspectorProperty_Int::OnEnChangeValue()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CInspectorProperty::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	m_value = GetDlgItemInt(IDC_VALUE);
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
int	CInspectorProperty_Int::GetValue() const
{
	return m_value;
}
void CInspectorProperty_Int::SetValue(int v)
{
	m_value = v;
}




void CInspectorProperty_Int::OnEnUpdateValue()
{
}

