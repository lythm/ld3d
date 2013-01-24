#include "stdafx.h"
#include "InspectorProperty_FilePath.h"
#include "resource.h"


CInspectorProperty_FilePath::CInspectorProperty_FilePath(CString name) : CInspectorProperty_Simple(name, IDD_INSPECTOR_PROPERTY_FILEPATH)
{
}


CInspectorProperty_FilePath::~CInspectorProperty_FilePath(void)
{
}


BOOL CInspectorProperty_FilePath::OnInitDialog()
{
	CInspectorProperty::OnInitDialog();

	CMFCEditBrowseCtrl* pCtrl = (CMFCEditBrowseCtrl*)GetDlgItem(IDC_VALUE);

	pCtrl->EnableFileBrowseButton();
	//pCtrl->EnableBrowseButton();
	return TRUE;
}

