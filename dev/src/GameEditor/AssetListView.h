#pragma once


// CAssetListView ��ͼ

class CAssetListView : public CListView
{
	DECLARE_DYNCREATE(CAssetListView)

public:
	void							DisplayFolder(const boost::filesystem::path& root);


protected:
	CAssetListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CAssetListView();

	
	
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CImageList			m_FileViewImages;
	std::vector<boost::filesystem::path>	m_assetList;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


