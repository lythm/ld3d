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
	CInspectorPanel(CString name, void* pUserData = nullptr);   // 标准构造函数
	virtual ~CInspectorPanel();


	void										Fold();
	void										UnFold();
	bool										Folded();
	int											GetHeight();

	bool										Create(CInspectorCtrl* pInspector);
	bool										Create(const TCHAR* szName, const CRect& rc, CInspectorCtrl* pInspector);

	void										OnPropertyChanged(CInspectorProperty* pProp);

	void										AddProperty(CInspectorProperty* pProp);
	void										RemoveAll();

	void										SetUserData(void* pData);
	void*										GetUserData();
private:
	void										ShowProps();
private:
	CString										m_name;
	CInspectorCtrl*								m_pInspector;
	bool										m_bExpanded;

	CInspectorPanelBar*							m_pBar;
	std::vector<CInspectorProperty*>			m_propList;

	void*										m_pUserData;


protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
