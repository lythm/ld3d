#pragma once

#include "InspectorProperty_Simple.h"
#include "afxeditbrowsectrl.h"

class CInspectorProperty_FilePath : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_FilePath(CString name, const boost::filesystem::path& value, bool bDirectory = false, void* pUserData = nullptr, CString ext = L"", CString filter = L"");
	virtual ~CInspectorProperty_FilePath(void);

	virtual BOOL								OnInitDialog();

	boost::filesystem::path						GetValue();
	void										SetValue(const boost::filesystem::path& value);
private:

	virtual void								DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	enum { IDD = IDD_INSPECTOR_PROPERTY_FILEPATH };

private:
	boost::filesystem::path						m_initValue;
	bool										m_bDir;
	CMFCEditBrowseCtrl							m_edit;
	CString										m_ext;
	CString										m_filter;
public:
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnUpdateValue();
};

