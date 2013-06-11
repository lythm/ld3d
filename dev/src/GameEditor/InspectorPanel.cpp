// InspectorPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "InspectorPanel.h"
#include "afxdialogex.h"
#include "InspectorCtrl.h"
#include "InspectorProperty.h"

#include "InspectorPanelBar.h"


#include "InspectorProperty_Int.h"
#include "InspectorProperty_String.h"
#include "InspectorProperty_Color.h"
#include "InspectorProperty_Float.h"
#include "InspectorProperty_Bool.h"
#include "InspectorProperty_FilePath.h"
#include "InspectorProperty_Range.h"
#include "InspectorProperty_Transform.h"
#include "InspectorProperty_Signal.h"
#include "InspectorPanel.h"

// CInspectorPanel 对话框

IMPLEMENT_DYNAMIC(CInspectorPanel, CWnd)


BEGIN_MESSAGE_MAP(CInspectorPanel, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CInspectorPanel 消息处理程序

CInspectorPanel::CInspectorPanel(CString name, ld3d::PropertySetPtr pSet, void* pUserData)
{
	m_name = name;
	m_pInspector = nullptr;
	m_bExpanded = false;
	m_pBar = nullptr;
	m_pUserData = pUserData;
	m_pSet = pSet;

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
			if(pProp->IsVisible() == false)
			{
				continue;
			}
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
	
	GenProps();
	
	ShowProps();
	return 0;
}

void CInspectorPanel::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	ShowProps();

	CRect rc;
	GetClientRect(rc);

	m_pBar->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), INSPECTOR_CAPTION_HEIGHT, SWP_NOACTIVATE | SWP_NOZORDER);

	int offset = INSPECTOR_CAPTION_HEIGHT;

	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		CInspectorProperty* pProp = m_propList[i];

		if(pProp->IsVisible() == false)
		{
			continue;
		}
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

		pProp->ShowWindow(m_bExpanded && pProp->IsVisible() ? SW_SHOW : SW_HIDE);
		
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


CInspectorProperty* CInspectorPanel::CreateProperty(ld3d::Property* p)
{
	using namespace ld3d;

	CInspectorProperty* pProp = nullptr;
	switch(p->getType())
	{
	case property_type_filepath:
		{
			pProp = new CInspectorProperty_FilePath(p->getName().c_str(), p, false);
		}
		break;
	case property_type_matrix44:
		{
			math::Matrix44 v = ((Matrix44Property*)p)->Get();

			pProp = new CInspectorProperty_Transform(p->getName().c_str(), p);
		}
		break;
	case property_type_string:
		{
			pProp = new CInspectorProperty_String(p->getName().c_str(),p);

		}
		break;
	case property_type_bool:
		{
			pProp = new CInspectorProperty_Bool(p->getName().c_str(), p);
		}
		break;
	case property_type_int:
		{
			pProp = new CInspectorProperty_Int(p->getName().c_str(), p);
			
		}
		break;
	case property_type_float:
		{
			pProp = new CInspectorProperty_Float(p->getName().c_str(), p);
		}
		break;
	case property_type_color:
		{
			pProp = new CInspectorProperty_Color(p->getName().c_str(), p);
		}
		break;
	case property_type_signal:
		{
			pProp = new CInspectorProperty_Signal(p->getName().c_str(), p);
		}
	default:
		break;
	}
	
	return pProp;
}
void CInspectorPanel::GenProps()
{
	for(size_t ii = 0; ii < m_pSet->getPropertyCount(); ++ii)
	{
		ld3d::Property* p = m_pSet->getProperty(ii);
		CInspectorProperty* pSub = CreateProperty(p);

		AddProperty(pSub);
	}
}
void CInspectorPanel::ReBuildProperty()
{
	RemoveAll();
	GenProps();
}
void CInspectorPanel::RefreshLayout()
{
	m_pInspector->AdjustLayout();
}
CString CInspectorPanel::GetName()
{
	return m_name;
}
CInspectorProperty*	CInspectorPanel::FindProperty(CString name)
{
	for(size_t i = 0; i < m_propList.size(); ++i)
	{
		if(m_propList[i]->GetName() == name)
		{
			return m_propList[i];
		}
	}
	return nullptr;

}