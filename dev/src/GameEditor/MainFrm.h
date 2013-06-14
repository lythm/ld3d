
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "AssetView.h"
#include "ObjectView.h"
#include "OutputWnd.h"
#include "TemplateView.h"
#include "InspectorView.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	CObjectView*			GetObjectView();
	COutputWnd*				GetOutput();

	void					SetFPS(float fps);

	bool					UpdateComClassMap();
	bool					UpdateTemplateMap();

	void					UpdateObjectView(ld3d::GameObjectPtr pRoot);
	void					UpdateGameObjectProperty(ld3d::GameObjectPtr pObj);
	void					OutputInfo(const CString& info);
	void					OutputBuild(const CString& build);
	void					UpdateAssetsView();

	void					Inspector_AdjustLayout();
	CInspector*				GetInspector();
private:
	bool					UpdateComponentMenu(CMFCPopupMenu* pMenu);
	ld3d::ExtPackage::ComponentClass* FindClassByMenuID(UINT uID);

	bool					UpdateTemplateMenu(CMFCPopupMenu* pMenu);
	ld3d::GameObjectTemplate* FindTemplateByMenuID(UINT uID);
// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CAssetView         m_wndAssetView;
	CObjectView        m_wndObjectView;
	COutputWnd        m_wndOutput;
	CMFCCaptionBar    m_wndCaptionBar;
	CTemplateView	  m_wndTplView;
	CInspectorView		m_wndInspectorView;
	std::unordered_map<std::wstring, std::vector<ld3d::ExtPackage::ComponentClass*> >	m_ComClassMap;
	std::unordered_map<std::wstring, std::vector<ld3d::GameObjectTemplate*> >			m_templateMap;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateCaptionBar();
public:
	afx_msg void OnClose();
	afx_msg void OnGameobjectCreateempty();
	afx_msg void OnComponentMenu(UINT nID);
	afx_msg void OnCreateFromTemplateMenu(UINT nID);
	afx_msg void OnUpdateComponentMenuUI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateFromTemplateMenuUI(CCmdUI* pCmdUI);
	
	afx_msg void OnViewShowgrid();
	afx_msg void OnUpdateViewShowgrid(CCmdUI *pCmdUI);
	afx_msg void OnEditAppsettings();
	afx_msg void OnImportImportmaxmesh();
	virtual BOOL OnShowPopupMenu(CMFCPopupMenu* pMenuPopup);
	virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnRenderingSetting();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBuildPreview();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSaveScene();
	afx_msg void OnFileOpenScene();
	afx_msg void OnFileSaveSceneAs();
	afx_msg void OnFileNewScene();
	afx_msg void OnFileNewProject();
	afx_msg void OnFileOpenProject();
	afx_msg void OnFileSaveProject();
};


