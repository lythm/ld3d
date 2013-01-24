#include "stdafx.h"
#include "InspectorProperty_Float.h"

#include "resource.h"



CInspectorProperty_Float::CInspectorProperty_Float(CString name) : CInspectorProperty_Simple(name, IDD_INSPECTOR_PROPERTY_FLOAT)
, m_value(0)
{
}


CInspectorProperty_Float::~CInspectorProperty_Float(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Float, CInspectorProperty_Simple)

END_MESSAGE_MAP()


void CInspectorProperty_Float::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BOOL CInspectorProperty_Float::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());

	return TRUE;
}
