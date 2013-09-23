
// GameEditorView.cpp : CGameEditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GameEditor.h"
#endif

#include "GameEditorDoc.h"
#include "GameEditorView.h"


#include "MainFrm.h"
#include "ObjectView.h"

#include "GridMesh.h"
#include "Renderer.h"


#include "editor_utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameEditorView

IMPLEMENT_DYNCREATE(CGameEditorView, CView)

BEGIN_MESSAGE_MAP(CGameEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGameEditorView ����/����

CGameEditorView::CGameEditorView()
{
	// TODO: �ڴ˴���ӹ������

//	m_pGrid = NULL;

}

CGameEditorView::~CGameEditorView()
{
	
}

BOOL CGameEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGameEditorView ����

void CGameEditorView::OnDraw(CDC* pDC)
{
	CGameEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

void CGameEditorView::OnRButtonUp(UINT nFlags , CPoint point)
{

	RendererPtr pRenderer = Project::Instance()->GetRenderer();

	if(pRenderer)
	{
		pRenderer->OnMouseRButtonUp(nFlags, point);
	}

	
	ClientToScreen(&point);
	OnContextMenu(this, point);
	
}

void CGameEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameEditorView ���

#ifdef _DEBUG
void CGameEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGameEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameEditorDoc* CGameEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameEditorDoc)));
	return (CGameEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameEditorView ��Ϣ�������


void CGameEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
}



void CGameEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnTimer(nIDEvent);
}


void CGameEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(cx != 0 && cy != 0)
	{
		Project::Instance()->ResizeRenderer(cx, cy);
		
	}
}

void CGameEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	RendererPtr pRenderer = Project::Instance()->GetRenderer();
	
	if(pRenderer)
	{
		pRenderer->OnMouseMove(nFlags, point);
	}

	CView::OnMouseMove(nFlags, point);
}


void CGameEditorView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���


}


void CGameEditorView::OnDestroy()
{
	//AppContext::ReleaseContext();
	util_set_rendering_wnd(nullptr);
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}


void CGameEditorView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ



	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CGameEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RendererPtr pRenderer = Project::Instance()->GetRenderer();

	if(pRenderer)
	{
		pRenderer->OnMouseWheel(nFlags, zDelta, pt);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CGameEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	RendererPtr pRenderer = Project::Instance()->GetRenderer();

	if(pRenderer)
	{
		pRenderer->OnMouseRButtonDown(nFlags, point);
	}

	CView::OnRButtonDown(nFlags, point);
}


BOOL CGameEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rc;
	GetClientRect(rc);
	CBrush br(RGB(0, 0,0));
	pDC->FillRect(rc, &br);

	return TRUE;
}


int CGameEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	util_set_rendering_wnd(this);
		
	return 0;
}


void CGameEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CGameEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(Project::Instance()->GetRenderer())
	{
		Project::Instance()->GetRenderer()->OnMouseLButtonClick(nFlags, point);
	}
	CView::OnLButtonUp(nFlags, point);
}

