#pragma once

//namespace controls
//{
	class CPropertyWnd: public CWnd
	{
	};

#define INSPECTOR_PANEL_HEIGHT				20
	class CInspectorPanel: public CDialogEx
	{
	public:
		CInspectorPanel(CBrush* pBkBrush);
		virtual ~CInspectorPanel();

		void										Fold();
		void										UnFold();

		int											GetHeight();

		bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);

	private:
		CWnd*										m_pContentWnd;
		CBrush*										m_pBkBrush;
		CString										m_name;
	public:
		DECLARE_MESSAGE_MAP()
		afx_msg void OnPaint();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		virtual BOOL OnInitDialog();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	};
	class CInspectorCtrl : public CWnd
	{
	public:
		CInspectorCtrl(void);
		virtual ~CInspectorCtrl(void);


		bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);
		void										AddPanel(CInspectorPanel* pPanel);
	private:

		std::vector<CInspectorPanel*>				m_panels;
		CBrush*										m_pannelBk;
		CBrush*										m_pBkBrush;
	public:
		DECLARE_MESSAGE_MAP()
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnDestroy();
	};


//}
