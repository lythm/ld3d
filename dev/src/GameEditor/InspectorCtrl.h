#pragma once

class CInspectorPanel;
class CInspectorProperty;

class CInspectorCtrl : public CWnd
{
public:
	CInspectorCtrl(void);
	virtual ~CInspectorCtrl(void);


	bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);
	void										AddPanel(CInspectorPanel* pPanel);
	int											GetPanelCount();
	CInspectorPanel*							GetPanel(int index);
	void										AdjustLayout();
	
	void										RemoveAll();
	virtual void								OnPropertyChanged(CInspectorProperty* pProp);
	virtual void								OnPanelEnabled(CInspectorPanel* pPanel, bool bEnabled);


	CInspectorProperty*							FindProperty(CString panel, CString name);

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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

