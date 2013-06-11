#include "stdafx.h"
#include "InspectorProperty_Signal.h"
#include "InspectorPanel.h"

CInspectorProperty_Signal::CInspectorProperty_Signal(CString name, ld3d::Property* pProp) : CInspectorProperty(name, pProp, NULL, IDD_INSPECTOR_PROPERTY_SIGNAL)
{
}


CInspectorProperty_Signal::~CInspectorProperty_Signal(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorProperty_Signal, CInspectorProperty)
	ON_WM_SIZE()
	ON_COMMAND(IDC_SIGNAL_BTN, &CInspectorProperty_Signal::OnSignalBtn)
END_MESSAGE_MAP()


void CInspectorProperty_Signal::OnSize(UINT nType, int cx, int cy)
{
	CInspectorProperty::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	CWnd* pWnd = GetDlgItem(IDC_SIGNAL_BTN);
	if(pWnd)
	{
		pWnd->SetWindowPos(nullptr, 
					rc.left + INSPECTOR_PROPERTY_ROW_H_PADDING, 
					rc.top + INSPECTOR_PROPERTY_ROW_V_PADDING, 
					rc.Width() - INSPECTOR_PROPERTY_ROW_H_PADDING, 
					rc.Height() - INSPECTOR_PROPERTY_ROW_V_PADDING, 
					SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


BOOL CInspectorProperty_Signal::OnInitDialog()
{
	CInspectorProperty::OnInitDialog();

	CWnd* pWnd = GetDlgItem(IDC_SIGNAL_BTN);
	if(pWnd && GetProperty())
	{
		pWnd->SetWindowTextW(GetName());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CInspectorProperty_Signal::OnSignalBtn()
{
	if(GetProperty())
	{
		((ld3d::Property_T<ld3d::prop_signal>*)GetProperty())->Set(ld3d::prop_signal());
	}

	OnValueChanged();
}
