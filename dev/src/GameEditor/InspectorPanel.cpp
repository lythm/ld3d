// InspectorPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "InspectorPanel.h"
#include "afxdialogex.h"
#include "InspectorCtrl.h"
#include "InspectorProperty.h"

#include "InspectorPanelBar.h"

// CInspectorPanel 对话框

IMPLEMENT_DYNAMIC(CInspectorPanel, CWnd)


BEGIN_MESSAGE_MAP(CInspectorPanel, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CInspectorPanel 消息处理程序

CInspectorPanel::CInspectorPanel(CString name, void* pUserData)
{
	m_name = name;
	m_pInspector = nullptr;
	m_bExpanded = false;
	m_pBar = nullptr;
	m_pUserData = pUserData;

}
CInspectorPanel::~CInspectorPanel()
{
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		delete m_propList[i];
	}
	m_propList.clear();
	delete m_pBar;
	m_pBar = nullptr;
}
void CInspectorPanel::RemoveAll()
{
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		m_propList[i]->DestroyWindow();
		delete m_propList[i];
	}
	m_propList.clear();
}

bool CInspectorPanel::Folded()
{
	return !m_bExpanded;
}
void CInspectorPanel::Fold()
{
	m_bExpanded = false;
	ShowProps();

	m_pInspector->AdjustLayout();
}
void CInspectorPanel::UnFold()
{
	m_bExpanded = true;
	ShowProps();

	m_pInspector->AdjustLayout();
}
int	CInspectorPanel::GetHeight()
{
	int height = m_pBar->GetHeight();
	if(m_bExpanded)
	{
		for(size_t i = 0; i < m_propList.size(); ++i)
		{
			CInspectorProperty* pProp = m_propList[i];

			CRect propRc;
			pProp->GetClientRect(propRc);

			height += propRc.Height();
		}
	}
	height;
	return height;
}
bool CInspectorPanel::Create(CInspectorCtrl* pInspector)
{
	return Create(m_name, CRect(), pInspector);
}
bool CInspectorPanel::Create(const TCHAR* szName, const CRect& rc, CInspectorCtrl* pInspector)
{
	CString strClassName = GetGlobalData()->RegisterWindowClass(_T("GameEditor:InspectorPanel"));
	m_name = szName;
	m_pInspector = pInspector;
	return CWnd::Create(strClassName, szName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rc, pInspector, 0) == TRUE;
}


int CInspectorPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	m_pBar = new CInspectorPanelBar(m_name);

	if(false == m_pBar->Create(this))
	{
		assert(0);
		return -1;
	}
	m_pBar->ShowWindow(SW_SHOW);
	
	
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		if(false == m_propList[i]->Create(this))
		{
			assert(0);
			return -1;
		}
	}

	ShowProps();
	return 0;
}

void CInspectorPanel::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);

	m_pBar->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), INSPECTOR_CAPTION_HEIGHT, SWP_NOACTIVATE | SWP_NOZORDER);

	int offset = INSPECTOR_CAPTION_HEIGHT;

	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		CInspectorProperty* pProp = m_propList[i];

		CRect propRc;
		pProp->GetClientRect(propRc);

		pProp->SetWindowPos(NULL, rc.left, offset, rc.Width(), pProp->GetHeight(), SWP_NOACTIVATE | SWP_NOZORDER);

		offset += propRc.Height();
	}
}

void CInspectorPanel::ShowProps()
{
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		CInspectorProperty* pProp = m_propList[i];

		pProp->ShowWindow(m_bExpanded ? SW_SHOW : SW_HIDE);
		
	}
}
void CInspectorPanel::OnPropertyChanged(CInspectorProperty* pProp)
{
	m_pInspector->OnPropertyChanged(pProp);
}

void CInspectorPanel::AddProperty(CInspectorProperty* pProp)
{
	if(pProp == nullptr)
	{
		return;
	}
	if(m_hWnd != nullptr)
	{
		pProp->Create(this);
	}
	m_propList.push_back(pProp);
}
void CInspectorPanel::SetUserData(void* pData)
{
	m_pUserData = pData;
}
void* CInspectorPanel::GetUserData()
{
	return m_pUserData;
}