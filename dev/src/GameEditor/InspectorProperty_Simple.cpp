#include "stdafx.h"
#include "InspectorProperty_Simple.h"


CInspectorProperty_Simple::CInspectorProperty_Simple(CString name, void* pUserData, UINT nIDD) : CInspectorProperty(name, pUserData, nIDD)
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
		pWnd->SetWindowPos(nullptr, rc.left + H_PADDING, rc.top + V_PADDING, rc.Width() / 2, rc.Height() - V_PADDING, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	pWnd = GetDlgItem(IDC_VALUE);
	if(pWnd)
	{
		pWnd->SetWindowPos(nullptr, rc.Width() / 2, rc.top + V_PADDING, rc.Width() / 2 - H_PADDING, rc.Height() - V_PADDING, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}
