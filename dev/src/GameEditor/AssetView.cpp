
#include "stdafx.h"
#include "mainfrm.h"
#include "AssetView.h"
#include "Resource.h"
#include "GameEditor.h"
#include "AssetFolderTreeView.h"
#include "AssetListView.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CAssetView::CAssetView()
{
}

CAssetView::~CAssetView()
{
}

BEGIN_MESSAGE_MAP(CAssetView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CAssetView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_splitterWnd.CreateStatic(this, 1, 2);

	m_splitterWnd.CreateView(0, 0, RUNTIME_CLASS(CAssetFolderTreeView), CSize(300, 500), nullptr);
	m_splitterWnd.CreateView(0, 1, RUNTIME_CLASS(CAssetListView), CSize(300, 500), nullptr);

	((CAssetFolderTreeView*)m_splitterWnd.GetPane(0, 0))->SetAssetView(this);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_EX_DOUBLEBUFFER | TVS_TRACKSELECT | TVS_SHOWSELALWAYS| TVS_EDITLABELS | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	//if (!m_wndAssetView.Create(dwViewStyle, rectDummy, this, 4))
	//{
	//	TRACE0("未能创建文件视图\n");
	//	return -1;      // 未能创建
	//}

	
	//m_wndAssetView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	//FillFileView();

	//ScanFolder(L"./assets");

	AdjustLayout();

	return 0;
}

void CAssetView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CAssetView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	return;

	//CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndAssetView;
	//ASSERT_VALID(pWndTree);

	//if (pWnd != pWndTree)
	//{
	//	CDockablePane::OnContextMenu(pWnd, point);
	//	return;
	//}

	//if (point != CPoint(-1, -1))
	//{
	//	// 选择已单击的项:
	//	CPoint ptTree = point;
	//	pWndTree->ScreenToClient(&ptTree);

	//	UINT flags = 0;
	//	HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
	//	if (hTreeItem != NULL)
	//	{
	//		pWndTree->SelectItem(hTreeItem);
	//	}
	//}

	//pWndTree->SetFocus();
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CAssetView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_splitterWnd.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CAssetView::OnProperties()
{
	AfxMessageBox(_T("属性...."));

}

void CAssetView::OnFileOpen()
{
	// TODO: 在此处添加命令处理程序代码
}

void CAssetView::OnFileOpenWith()
{
	// TODO: 在此处添加命令处理程序代码
}

void CAssetView::OnDummyCompile()
{
	// TODO: 在此处添加命令处理程序代码
}

void CAssetView::OnEditCut()
{
	// TODO: 在此处添加命令处理程序代码
}

void CAssetView::OnEditCopy()
{
	// TODO: 在此处添加命令处理程序代码
}

void CAssetView::OnEditClear()
{
	// TODO: 在此处添加命令处理程序代码
}

void CAssetView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	/*CRect rectTree;
	m_wndAssetView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));*/
}

void CAssetView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_splitterWnd.SetFocus();
}

void CAssetView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定*/);
}

void CAssetView::ScanFolder(const CString& path)
{
	
	CAssetFolderTreeView* pView =  (CAssetFolderTreeView* )m_splitterWnd.GetPane(0, 0);

	pView->ScanFolder(path);

}
void CAssetView::DisplayFolder(const boost::filesystem::path& p)
{
	CAssetListView* pView = (CAssetListView*)m_splitterWnd.GetPane(0, 1);
	pView->DisplayFolder(p);
}
