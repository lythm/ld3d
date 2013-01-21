#pragma once

#include "InspectorCtrl.h"

class CInspectorToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};
class CInspectorView : public CDockablePane
{
// 构造
public:
	CInspectorView();

	void AdjustLayout();

// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		//m_wndPropList.SetVSDotNetLook(bSet);
		//m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CInspectorToolBar m_wndToolBar;
	//controls::CInspectorCtrl m_wndInspector;
	CInspectorCtrl m_wndInspector;
// 实现
public:
	virtual ~CInspectorView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void SetPropListFont();

	int m_nComboHeight;
public:
	afx_msg void OnDestroy();
};

