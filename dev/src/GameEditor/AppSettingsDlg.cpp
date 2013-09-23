// AppSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AppSettingsDlg.h"
#include "afxdialogex.h"
#include "editor_utils.h"

// CAppSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CAppSettingsDlg, CDialogEx)

CAppSettingsDlg::CAppSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppSettingsDlg::IDD, pParent)
{

}

CAppSettingsDlg::~CAppSettingsDlg()
{
}

void CAppSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAppSettingsDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CAppSettingsDlg::OnDeltaposSpin1)
END_MESSAGE_MAP()


// CAppSettingsDlg ��Ϣ�������


void CAppSettingsDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	CString str;

	str.Format(L"%d,%d", pNMUpDown->iDelta, pNMUpDown->iPos);

	util_log_info(str.GetString());
}
