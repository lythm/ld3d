#include "stdafx.h"
#include "InspectorProperty_Color.h"

#include "resource.h"


CInspectorProperty_Color::CInspectorProperty_Color(CString name) :CInspectorProperty_Simple(name, IDD_INSPECTOR_PROPERTY_COLOR)
{
}


CInspectorProperty_Color::~CInspectorProperty_Color(void)
{
}


BOOL CInspectorProperty_Color::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	CMFCColorButton* pButton = (CMFCColorButton* )GetDlgItem(IDC_VALUE);

	pButton->EnableOtherButton(L"Other");
	
	return true;
}
