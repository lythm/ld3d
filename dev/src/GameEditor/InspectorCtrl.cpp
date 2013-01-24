#include "stdafx.h"
#include "InspectorCtrl.h"

#include "resource.h"
#include "InspectorPanel.h"

//namespace controls
//{
CInspectorCtrl::CInspectorCtrl(void)
{
}


CInspectorCtrl::~CInspectorCtrl(void)
{
	for(size_t i = 0; i < m_panels.size(); ++i)
	{
		delete m_panels[i];
	}
	m_panels.clear();
	m_bkBrush.DeleteObject();
}
BEGIN_MESSAGE_MAP(CInspectorCtrl, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CInspectorCtrl::AddPanel(CInspectorPanel* pPanel)
{
	m_panels.push_back(pPanel);
}
int CInspectorCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	m_bkBrush.CreateSolidBrush(RGB(83, 83, 83));
	CRect rc;
	GetClientRect(&rc);


	for(int i = 0; i < 10; ++i)
	{
		rc.top = i * 30;
		rc.bottom = rc.top + 30;

		CInspectorPanel* pPanel = new CInspectorPanel(this);
		CString name;
		name.Format(L"T%d", i);
		pPanel->Create(name, rc, this);

		pPanel->ShowWindow(SW_SHOW);
		AddPanel(pPanel);
	}

	//ShowScrollBar(SB_VERT);
	//SetScoll
	return 0;
}
bool CInspectorCtrl::Create(const TCHAR* szName, const CRect& rc, CWnd* pParent)
{
	CString strClassName = GetGlobalData()->RegisterWindowClass(_T("GameEditor:InspectorCtrl"));

	return CWnd::Create(strClassName, szName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rc, pParent, IDD_INSPECTOR_VIEW) == TRUE;
}
void CInspectorCtrl::RefreshPanels()
{
	for(size_t i = 0; i < m_panels.size(); ++i)
	{
		CInspectorPanel* pPanel = m_panels[i];

		pPanel->InvalidatePanel();
	}

	Invalidate();
}
void CInspectorCtrl::AdjustLayout()
{
	CRect rc;
	GetClientRect(rc);

	int h = 0;
	for(size_t i = 0; i < m_panels.size(); ++i)
	{
		CInspectorPanel* pPanel = m_panels[i];

		pPanel->SetWindowPos(NULL, rc.left, rc.top + h, rc.Width(), pPanel->GetHeight(), SWP_NOACTIVATE | SWP_NOZORDER);

		int dh = pPanel->GetHeight() + 1;
		h += dh;
	}
}
void CInspectorCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	AdjustLayout();
	
	// TODO: �ڴ˴������Ϣ����������
}


BOOL CInspectorCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rc;

	GetClientRect(rc);

	pDC->FillRect(rc, &m_bkBrush);

	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CInspectorCtrl::OnDestroy()
{
	CWnd::OnDestroy();

}


void CInspectorCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}
