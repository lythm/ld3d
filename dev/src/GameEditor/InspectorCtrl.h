#pragma once

class CInspectorPanel;

class CInspectorCtrl : public CWnd
{
public:
	CInspectorCtrl(void);
	virtual ~CInspectorCtrl(void);


	bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);
	void										AddPanel(CInspectorPanel* pPanel);

	void										AdjustLayout();

	void										RefreshPanels();
private:

	std::vector<CInspectorPanel*>				m_panels;
	CBrush										m_bkBrush;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

