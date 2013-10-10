#include "stdafx.h"
#include "InspectorProperty_Int.h"
#include "resource.h"
#include "editor_utils.h"
#include <locale>


CInspectorProperty_Int::CInspectorProperty_Int(CString name, ld3d::Property* pProp, void* pUserData) : CInspectorProperty_Simple(name, pProp, pUserData, IDD_INSPECTOR_PROPERTY_INT)
{
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
	

	ld3d::Property_T<int> * pProp = (ld3d::Property_T<int>*)GetProperty();
	SetValue(pProp->Get());
	m_valueEdit.SetReadOnly(pProp->IsReadOnly());
	return TRUE;
}

void CInspectorProperty_Int::OnEnChangeValue()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CInspectorProperty::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

		
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
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
	ld3d::Property_T<int> * pProp = (ld3d::Property_T<int>*)GetProperty();

	pProp->Set(GetValue());

	OnValueChanged();
}