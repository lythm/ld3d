// AssetFolderTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "AssetFolderTreeView.h"


// CAssetFolderTreeView

IMPLEMENT_DYNCREATE(CAssetFolderTreeView, CTreeView)

CAssetFolderTreeView::CAssetFolderTreeView()
{

}

CAssetFolderTreeView::~CAssetFolderTreeView()
{
}

BEGIN_MESSAGE_MAP(CAssetFolderTreeView, CTreeView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CAssetFolderTreeView 诊断

#ifdef _DEBUG
void CAssetFolderTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CAssetFolderTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAssetFolderTreeView 消息处理程序


int CAssetFolderTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetTreeCtrl().SetTextColor(RGB(200,200,200));
	GetTreeCtrl().SetBkColor(RGB(83, 83, 83));

	GetTreeCtrl().ModifyStyle(0, TVS_HASLINES | TVS_EX_DOUBLEBUFFER | TVS_TRACKSELECT | TVS_SHOWSELALWAYS| TVS_EDITLABELS | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return -1;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

//	m_wndAssetView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	GetTreeCtrl().SetImageList(&m_FileViewImages, TVSIL_NORMAL);
	return 0;
}




void CAssetFolderTreeView::ScanFolder(const CString& path)
{
	
	using namespace boost;
	using namespace boost::filesystem;

	filesystem::path p(path);

	if(exists(p) == false)
	{
		return;
	}

	GetTreeCtrl().DeleteAllItems();
	HTREEITEM root = GetTreeCtrl().GetRootItem();
	_fill_view(p, root);

	GetTreeCtrl().Expand(root, TVE_EXPAND);

}
void CAssetFolderTreeView::_fill_view(boost::filesystem::path p, HTREEITEM hParent)
{
	using namespace boost;
	using namespace boost::filesystem;

	if(is_directory(p) == false)
	{
		//AddFileItem(hParent, p);
		return;
	}

	HTREEITEM hNode = AddDirectoryItem(hParent, p);
	
	directory_iterator it(p);

	for(;it != directory_iterator(); ++it)
	{
		_fill_view(it->path(), hNode);
	}
	GetTreeCtrl().Expand(hNode, TVE_EXPAND);
}
HTREEITEM CAssetFolderTreeView::AddFileItem(HTREEITEM hParent, boost::filesystem::path p)
{
	using namespace ld3d;


	if(p.extension() == ".gp")
	{
		return nullptr;
	}
	HTREEITEM item = GetTreeCtrl().InsertItem(p.filename().wstring().c_str(), 2, 2, hParent);

	return item;
}
HTREEITEM CAssetFolderTreeView::AddDirectoryItem(HTREEITEM hParent, boost::filesystem::path p)
{
	HTREEITEM item = GetTreeCtrl().InsertItem(p.filename().wstring().c_str(), 0, 0, hParent);


	return item;
}
