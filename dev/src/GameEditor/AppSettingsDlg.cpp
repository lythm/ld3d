// AppSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AppSettingsDlg.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CAppSettingsDlg ��Ϣ�������
