#include "stdafx.h"
#include "InspectorCtrl.h"

#include "resource.h"

//namespace controls
//{
	CInspectorCtrl::CInspectorCtrl(void)
	{
	}


	CInspectorCtrl::~CInspectorCtrl(void)
	{
	}
	BEGIN_MESSAGE_MAP(CInspectorCtrl, CWnd)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
	END_MESSAGE_MAP()

	void CInspectorCtrl::AddPanel(CInspectorPanel* pPanel)
	{
		m_panels.push_back(pPanel);
	}
	int CInspectorCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CWnd::OnCreate(lpCreateStruct) == -1)
			return -1;

		CRect rc;
		GetClientRect(&rc);
		

		for(int i = 0; i < 10; ++i)
		{
			rc.top = i * 30;
			rc.bottom = rc.top + 30;

			CInspectorPanel* pPanel = new CInspectorPanel;
			pPanel->Create(L"T1", rc, this);

			pPanel->ShowWindow(SW_SHOW);
			AddPanel(pPanel);
		}
		return 0;
	}
	bool CInspectorCtrl::Create(const TCHAR* szName, const CRect& rc, CWnd* pParent)
	{
		CString strClassName = GetGlobalData()->RegisterWindowClass(_T("GameEditor:InspectorCtrl"));

		return CWnd::Create(strClassName, szName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rc, pParent, IDD_INSPECTOR_VIEW) == TRUE;
	}


	void CInspectorCtrl::OnSize(UINT nType, int cx, int cy)
	{
		CWnd::OnSize(nType, cx, cy);

		CRect rc;
		GetClientRect(rc);

		for(size_t i = 0; i < m_panels.size(); ++i)
		{
			CInspectorPanel* pPanel = m_panels[i];

			pPanel->SetWindowPos(NULL, rc.left, rc.top + i * 20, rc.Width(), 19, SWP_NOACTIVATE | SWP_NOZORDER);
		}
		// TODO: 在此处添加消息处理程序代码
	}

	CInspectorPanel::CInspectorPanel()
	{
		m_pContentWnd = nullptr;
	}
	CInspectorPanel::~CInspectorPanel()
	{
	}
	void CInspectorPanel::Fold()
	{
	}
	void CInspectorPanel::UnFold()
	{
	}
	int	CInspectorPanel::GetHeight()
	{
		return 0;
	}
	bool CInspectorPanel::Create(const TCHAR* szName, const CRect& rc, CWnd* pParent)
	{
		//CString strClassName = GetGlobalData()->RegisterWindowClass(_T("GameEditor:InspectorPanel"));
		m_name = szName;
		return CDialogEx::Create(IDD_INSPECTOR_PANEL, pParent);
			//strClassName, szName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rc, pParent, IDD_INSPECTOR_PANEL) == TRUE;
	}
	


	void CInspectorPanel::OnPaint()
	{
		CPaintDC dc(this); // device context for painting
	
	}
	
	int CInspectorPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CDialogEx::OnCreate(lpCreateStruct) == -1)
			return -1;

		
		
		return 0;
	}
	BEGIN_MESSAGE_MAP(CInspectorPanel, CWnd)
		ON_WM_PAINT()
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
	END_MESSAGE_MAP()

	//}


	BOOL CInspectorPanel::OnInitDialog()
	{
		CDialogEx::OnInitDialog();

		CWnd * pText = (CWnd*)GetDlgItem(IDC_NAME);
		pText->SetWindowTextW(m_name);

		return TRUE;
	}


	void CInspectorPanel::OnSize(UINT nType, int cx, int cy)
	{
		CDialogEx::OnSize(nType, cx, cy);

		CRect rc;
		GetClientRect(rc);
		
		CWnd * pText = (CWnd*)GetDlgItem(IDC_NAME);
		
		//pText->SetWindowPos(NULL, rc.left + 100, rc.top, rc.Width() - 20, rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

		Invalidate();
	}


	BOOL CInspectorPanel::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CRect rc;

		GetClientRect(rc);

		pDC->FillRect(rc, new CBrush(RGB(70, 70, 70)));
		
		return TRUE;
		//return CDialogEx::OnEraseBkgnd(pDC);
	}


	BOOL CInspectorCtrl::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CRect rc;

		GetClientRect(rc);

		pDC->FillRect(rc, new CBrush(RGB(83, 83, 83)));
		
		return TRUE;
		//return CWnd::OnEraseBkgnd(pDC);
	}
