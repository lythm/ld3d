// PreviewWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameEditor.h"
#include "PreviewWnd.h"
#include "afxdialogex.h"

#include "Project.h"


// CPreviewWnd �Ի���

IMPLEMENT_DYNAMIC(CPreviewWnd, CDialogEx)

CPreviewWnd::CPreviewWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPreviewWnd::IDD, pParent)
{

}

CPreviewWnd::~CPreviewWnd()
{
}

void CPreviewWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreviewWnd, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPreviewWnd ��Ϣ�������


BOOL CPreviewWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	using namespace ld3d;

	CRect rc;

	GetClientRect(rc);


	m_pRenderTarget =Project::Instance()->GetCoreApi()->GetSysGraphics()->CreateRenderWindow(m_hWnd, rc.Width(), rc.Height(), G_FORMAT_R8G8B8A8_UNORM, G_FORMAT_D24_UNORM_S8_UINT, 2, 1, 0, true);
	
	Project::Instance()->GetCoreApi()->GetSysGraphics()->SetRenderWindow(m_pRenderTarget);
	Project::Instance()->ResizeRenderer(rc.Width(), rc.Height());
	
	SetTimer(99, 10, nullptr);

	return TRUE;
}


void CPreviewWnd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	KillTimer(99);

	ld3d::CoreApiPtr pCore = Project::Instance()->GetCoreApi();

	pCore->GetSysGraphics()->SetRenderWindow(ld3d::RenderTargetPtr());

	int w = pCore->GetSysGraphics()->GetFrameBufferWidth();
	int h = pCore->GetSysGraphics()->GetFrameBufferHeight();

	Project::Instance()->ResizeRenderer(w, h);

	m_pRenderTarget->Release();
	m_pRenderTarget.reset();


	CDialogEx::OnClose();
}



void CPreviewWnd::OnTimer(UINT_PTR nIDEvent)
{
	Project::Instance()->RenderPreview();
	
	CDialogEx::OnTimer(nIDEvent);
}


void CPreviewWnd::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_pRenderTarget != ld3d::RenderTargetPtr())
	{
		Project::Instance()->ResizeRenderer(cx, cy);
	}
	// TODO: �ڴ˴������Ϣ����������
}
