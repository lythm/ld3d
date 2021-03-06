#include "stdafx.h"
#include "InspectorProperty_Simple.h"


CInspectorProperty_Simple::CInspectorProperty_Simple(CString name, ld3d::Property* pProp, void* pUserData, UINT nIDD) : CInspectorProperty(name, pProp, pUserData, nIDD)
{
}


CInspectorProperty_Simple::~CInspectorProperty_Simple(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Simple, CInspectorProperty)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CInspectorProperty_Simple::OnSize(UINT nType, int cx, int cy)
{
	CInspectorProperty::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	CWnd* pWnd = GetDlgItem(IDC_NAME);
	if(pWnd)
	{
		pWnd->SetWindowPos(nullptr, 
					rc.left + INSPECTOR_PROPERTY_ROW_H_PADDING, 
					rc.top + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					rc.Width() / 2, 
					rc.Height() - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);
	}

	pWnd = GetDlgItem(IDC_VALUE);
	if(pWnd)
	{
		pWnd->SetWindowPos(nullptr, 
					rc.Width() / 2, 
					rc.top + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					rc.Width() / 2 - INSPECTOR_PROPERTY_ROW_H_PADDING, 
					rc.Height() - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);
	}
}
