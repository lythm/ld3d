// InspectorPanelBar.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "InspectorPanelBar.h"
#include "afxdialogex.h"
#include "resource.h"
#include "InspectorPanel.h"


// CInspectorPanelBar 对话框

IMPLEMENT_DYNAMIC(CInspectorPanelBar, CDialogEx)

CInspectorPanelBar::CInspectorPanelBar(CString name)
	: CDialogEx(CInspectorPanelBar::IDD, nullptr)
{
	m_name = name;
	m_pPanel = nullptr;
}

CInspectorPanelBar::~CInspectorPanelBar()
{
}

void CInspectorPanelBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
bool CInspectorPanelBar::Create(CInspectorPanel* pPanel)
{
	m_pPanel = pPanel;

	m_bkBrush.CreateSolidBrush(RGB(70, 70, 70));
	return CDialogEx::Create(CInspectorPanelBar::IDD, pPanel);
}

BEGIN_MESSAGE_MAP(CInspectorPanelBar, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_NAME, &CInspectorPanelBar::OnStnClickedName)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CInspectorPanelBar 消息处理程序


HBRUSH CInspectorPanelBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(200,200,200));
		pDC->SetBkColor(RGB(70, 70, 70));
	}
	
	return m_bkBrush;
}


BOOL CInspectorPanelBar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_NAME, m_name);

	return TRUE;
}


void CInspectorPanelBar::OnStnClickedName()
{
	m_pPanel->Folded() ? m_pPanel->UnFold() : m_pPanel->Fold();
}


void CInspectorPanelBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CWnd* pName = GetDlgItem(IDC_NAME);

	CRect rc;
	GetClientRect(rc);

	int left = rc.left;
	if(pName)
	{
		pName->SetWindowPos(NULL, left, rc.top, rc.Width() - 40, rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

//	CMFCMenuButton* pBtn = (CMFCMenuButton*)GetDlgItem(IDC_MENU_BTN);
	
	//left = rc.Width() - 40;

	//if(left >0)
	//{
	//	pBtn->SetWindowPos(NULL, left + 0, rc.top, left + 20, rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
//	}

	Invalidate();
}
int CInspectorPanelBar::GetHeight()
{
	CRect rc;
	GetClientRect(rc);

	return rc.Height();
}
