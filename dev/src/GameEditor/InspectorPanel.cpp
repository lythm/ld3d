// InspectorPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "InspectorPanel.h"
#include "afxdialogex.h"
#include "InspectorCtrl.h"
#include "InspectorProperty.h"


// CInspectorPanel 对话框

IMPLEMENT_DYNAMIC(CInspectorPanel, CDialogEx)


void CInspectorPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CInspectorPanel, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_STN_CLICKED(IDC_NAME, &CInspectorPanel::OnStnClickedName)
END_MESSAGE_MAP()



// CInspectorPanel 消息处理程序

CInspectorPanel::CInspectorPanel(CInspectorCtrl* pCtrl)
{
	m_pInspector = pCtrl;
	m_pContentWnd = nullptr;
	m_bExpanded = false;
}
CInspectorPanel::~CInspectorPanel()
{
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		delete m_propList[i];
	}
}
void CInspectorPanel::InvalidatePanel()
{
	UpdateWindow();
	Invalidate();

	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		m_propList[i]->UpdateWindow();
		m_propList[i]->Invalidate();
	}
}
void CInspectorPanel::Fold()
{
	m_bExpanded = false;
	ShowProps();

	m_pInspector->AdjustLayout();

	InvalidatePanel();
	m_pInspector->UpdateWindow();
	m_pInspector->Invalidate();

}
void CInspectorPanel::UnFold()
{
	m_bExpanded = true;
	ShowProps();

	m_pInspector->AdjustLayout();

	InvalidatePanel();
	m_pInspector->UpdateWindow();
	m_pInspector->Invalidate();
	
}
int	CInspectorPanel::GetHeight()
{
	if(m_bExpanded)
	{
		int height = INSPECTOR_CAPTION_HEIGHT;

		for(size_t i = 0; i < m_propList.size(); ++i)
		{
			CInspectorProperty* pProp = m_propList[i];

			CRect propRc;
			pProp->GetClientRect(propRc);

			height += propRc.Height();
		}

		return height;
	}

	return INSPECTOR_CAPTION_HEIGHT;
}
bool CInspectorPanel::Create(const TCHAR* szName, const CRect& rc, CWnd* pParent)
{
	//CString strClassName = GetGlobalData()->RegisterWindowClass(_T("GameEditor:InspectorPanel"));
	m_name = szName;

	m_bkBrush.CreateSolidBrush(RGB(70, 70, 70));


	return CDialogEx::Create(IDD_INSPECTOR_PANEL, pParent);
	//strClassName, szName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rc, pParent, IDD_INSPECTOR_PANEL) == TRUE;
}


int CInspectorPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
//}


BOOL CInspectorPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CStatic * pText = (CStatic*)GetDlgItem(IDC_NAME);
	pText->SetWindowTextW(m_name);


	CInspectorProperty* pProp = new CInspectorProperty;

	pProp->Create(this);
	m_propList.push_back(pProp);

	return TRUE;
}


void CInspectorPanel::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	CStatic * pText = (CStatic*)GetDlgItem(IDC_NAME);


	pText->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), INSPECTOR_CAPTION_HEIGHT, SWP_NOACTIVATE | SWP_NOZORDER);

	int offset = INSPECTOR_CAPTION_HEIGHT;

	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		CInspectorProperty* pProp = m_propList[i];

		CRect propRc;
		pProp->GetClientRect(propRc);

		pProp->SetWindowPos(NULL, rc.left, offset, rc.Width(), propRc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

		offset += propRc.Height();
	}

	Invalidate();
}


BOOL CInspectorPanel::OnEraseBkgnd(CDC* pDC)
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(rc);
	dc.FillRect(rc, &m_bkBrush);

	return TRUE;
}


HBRUSH CInspectorPanel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(200,200,200));
		pDC->SetBkColor(RGB(70, 70, 70));
	}
	return m_bkBrush;
}


void CInspectorPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CInspectorPanel::OnStnClickedName()
{
	m_bExpanded ? Fold() : UnFold();
}
void CInspectorPanel::ShowProps()
{
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		CInspectorProperty* pProp = m_propList[i];

		pProp->ShowWindow(m_bExpanded ? SW_SHOW : SW_HIDE);
	}
}


