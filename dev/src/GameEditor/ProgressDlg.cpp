// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameEditor.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg �Ի���

IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

	CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_INFO, m_progressInfo);
	DDX_Control(pDX, IDC_PROGRESS, m_progressBar);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CProgressDlg ��Ϣ�������


BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_progressBar.SetRange(0, 100);
	m_progressBar.SetPos(0);

	
	return TRUE;
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CProgressDlg::ProcessMessage()
{
	MSG msg = {0};
	if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

void CProgressDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: �ڴ˴������Ϣ����������
}


void CProgressDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}
void CProgressDlg::SetPos(int pos)
{
	m_progressBar.SetPos(pos);
}