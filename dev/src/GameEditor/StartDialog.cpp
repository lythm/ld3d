// StartDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StartDialog.h"
#include "afxdialogex.h"


// CStartDialog �Ի���

IMPLEMENT_DYNAMIC(CStartDialog, CDialogEx)

CStartDialog::CStartDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStartDialog::IDD, pParent)
{

}

CStartDialog::~CStartDialog()
{
}

void CStartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartDialog, CDialogEx)
END_MESSAGE_MAP()


// CStartDialog ��Ϣ�������
