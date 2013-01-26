
#pragma once

#include "AssetFolderTreeView.h"

class CAssetViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CAssetView : public CDockablePane
{
// 构造
public:
	CAssetView();

	void AdjustLayout();
	void OnChangeVisualStyle();


	void			ScanFolder(const CString& path);

	void			DisplayFolder(const boost::filesystem::path& p);

// 特性
protected:

	CSplitterWndEx		m_splitterWnd;
	CAssetViewToolBar	m_wndToolBar;

protected:

	
// 实现
public:
	virtual ~CAssetView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

