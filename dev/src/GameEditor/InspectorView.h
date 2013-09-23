#pragma once

#include "Inspector.h"

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


	void											UpdateGameObjectProperty(ld3d::GameObjectPtr pObj);
	CInspector*										GetInspector();
protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CInspector m_wndInspector;
// 实现
public:
	virtual ~CInspectorView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void SetPropListFont();

	int m_nComboHeight;
public:
	afx_msg void OnDestroy();
};

