// AssetListView.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "AssetListView.h"
#include "Project.h"


// CAssetListView

IMPLEMENT_DYNCREATE(CAssetListView, CListView)

CAssetListView::CAssetListView()
{

}

CAssetListView::~CAssetListView()
{
}

BEGIN_MESSAGE_MAP(CAssetListView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CAssetListView 诊断

#ifdef _DEBUG
void CAssetListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CAssetListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAssetListView 消息处理程序


int CAssetListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetListCtrl().ModifyStyle(LVS_SMALLICON, LVS_ICON);
	//GetListCtrl().ModifyStyle(LVS_ICON, LVS_SMALLICON);

	GetListCtrl().SetTextColor(RGB(200,200,200));
	GetListCtrl().SetBkColor(RGB(83, 83, 83));
	GetListCtrl().SetTextBkColor(RGB(83, 83, 83));

	



	UINT uiBmpId = IDB_ASSETLIST;

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

	nFlags |= ILC_COLOR24;

	m_FileViewImages.Create(bmpObj.bmWidth, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	GetListCtrl().SetImageList(&m_FileViewImages, LVSIL_NORMAL);
		

	DisplayFolder("./assets/standard/material");
	
	return 0;
}

void CAssetListView::DisplayFolder(const boost::filesystem::path& root)
{
	GetListCtrl().DeleteAllItems();

	using namespace boost::filesystem;

	if(is_directory(root) == false)
	{
		//AddFileItem(hParent, p);
		return;
	}

	directory_iterator it(root);

	for(;it != directory_iterator(); ++it)
	{
		if(is_directory(it->path()))
		{
			continue;
		}

		CString filename = it->path().filename().wstring().c_str();
		GetListCtrl().InsertItem(0, filename, 0);
	}

}