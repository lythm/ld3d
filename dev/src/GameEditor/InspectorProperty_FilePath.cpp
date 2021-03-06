#include "stdafx.h"
#include "InspectorProperty_FilePath.h"
#include "resource.h"


CInspectorProperty_FilePath::CInspectorProperty_FilePath(CString name, ld3d::Property* pProp, bool bDirectory, void* pUserData, CString ext, CString filter) 
	: CInspectorProperty_Simple(name, pProp, pUserData, IDD_INSPECTOR_PROPERTY_FILEPATH)
{
	m_bDir = bDirectory;
	m_ext = ext;
	m_filter = filter;
}


CInspectorProperty_FilePath::~CInspectorProperty_FilePath(void)
{
}


BOOL CInspectorProperty_FilePath::OnInitDialog()
{
	CInspectorProperty_Simple::OnInitDialog();

	SetDlgItemText(IDC_NAME, GetName());
	
	m_bDir ? m_edit.EnableFolderBrowseButton() : m_edit.EnableFileBrowseButton(m_ext, m_filter);
		
	ld3d::Property_T<const boost::filesystem::path> * pProp = (ld3d::Property_T<const boost::filesystem::path>*)GetProperty();

	SetValue(pProp->Get());

	m_edit.SetReadOnly(pProp->IsReadOnly());
	return TRUE;
}

void CInspectorProperty_FilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_VALUE, m_edit);
}
BEGIN_MESSAGE_MAP(CInspectorProperty_FilePath, CInspectorProperty_Simple)
	ON_EN_UPDATE(IDC_VALUE, &CInspectorProperty_FilePath::OnEnUpdateValue)
END_MESSAGE_MAP()


void CInspectorProperty_FilePath::OnEnUpdateValue()
{
	ld3d::Property_T<const boost::filesystem::path> * pProp = (ld3d::Property_T<const boost::filesystem::path>*)GetProperty();

	pProp->Set(GetValue());

	OnValueChanged();
}

boost::filesystem::path CInspectorProperty_FilePath::GetValue()
{
	CString str;
	m_edit.GetWindowText(str);

	return str.GetString();
}
void CInspectorProperty_FilePath::SetValue(const boost::filesystem::path& value)
{
	m_edit.SetWindowText(value.wstring().c_str());
}
