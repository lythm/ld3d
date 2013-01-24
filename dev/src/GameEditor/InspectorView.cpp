#include "stdafx.h"
#include "InspectorView.h"


#include "Resource.h"
#include "MainFrm.h"
#include "GameEditor.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CInspectorView::CInspectorView()
{
	m_nComboHeight = 0;
}

CInspectorView::~CInspectorView()
{
}

BEGIN_MESSAGE_MAP(CInspectorView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CInspectorView::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndInspector.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), rectClient.Height() -(m_nComboHeight), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CInspectorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if(false == m_wndInspector.Create(L"AAA", rectDummy, this))
	{
		DWORD ret = GetLastError();
		return -1;      // 未能创建

	}
	// 创建组合:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

	m_wndObjectCombo.AddString(_T("应用程序"));
	m_wndObjectCombo.AddString(_T("属性窗口"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	
	SetPropListFont();
	AdjustLayout();
	return 0;
}

void CInspectorView::OnSize(UINT nType, int cx, int cy)
{

	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CInspectorView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
}

void CInspectorView::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CInspectorView::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndObjectCombo.SetFont(&m_fntPropList);
	m_wndInspector.SetFont(&m_fntPropList);
}


void CInspectorView::OnDestroy()
{
	//UpdateGameObjectProp(ld3d::GameObjectPtr());
	CDockablePane::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
