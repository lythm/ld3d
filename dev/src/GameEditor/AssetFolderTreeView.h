#pragma once


// CAssetFolderTreeView ��ͼ

class CAssetFolderTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CAssetFolderTreeView)

public:
	void			ScanFolder(const CString& path);

protected:
	CAssetFolderTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CAssetFolderTreeView();

	


private:

	void			_fill_view(boost::filesystem::path p, HTREEITEM hParent);


	HTREEITEM		AddFileItem(HTREEITEM hParent, boost::filesystem::path p);
	HTREEITEM		AddDirectoryItem(HTREEITEM hParent, boost::filesystem::path p);

	CImageList			m_FileViewImages;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


