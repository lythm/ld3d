#pragma once

#define INSPECTOR_CAPTION_HEIGHT				20
// CInspectorPanel 对话框
class CInspectorCtrl;
class CInspectorProperty;
class CInspectorPanelBar;


class CInspectorPanel : public CWnd
{
	DECLARE_DYNAMIC(CInspectorPanel)

public:
	CInspectorPanel(CInspectorCtrl* pCtrl);   // 标准构造函数
	virtual ~CInspectorPanel();


	void										Fold();
	void										UnFold();
	bool										Folded();
	int											GetHeight();

	bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);

	void										InvalidatePanel();
private:
	void										ShowProps();
private:
	CString										m_name;
	CInspectorCtrl*								m_pInspector;
	bool										m_bExpanded;

	CInspectorPanelBar*							m_pBar;
	std::vector<CInspectorProperty*>			m_propList;


protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
