// InpsectorProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "InspectorProperty.h"
#include "afxdialogex.h"
#include "InspectorPanel.h"



// CInpsectorProperty 对话框

IMPLEMENT_DYNAMIC(CInspectorProperty, CDialogEx)

	CInspectorProperty::CInspectorProperty(CString name, ld3d::Property* pProp, void* pUserData, UINT nIDD)
	: CDialogEx(nIDD, nullptr)
{
	m_pProp = pProp;
	m_nIDD = nIDD;
	m_pPanel = nullptr;
	m_name = name;
	m_pUserData = pUserData;
	m_bReadOnly = false;
	m_bVisible = true;
}

CInspectorProperty::~CInspectorProperty()
{
	m_bkBrush.DeleteObject();
}
void CInspectorProperty::SetReadOnly(bool bReadOnly)
{
	m_bReadOnly = bReadOnly;
}
bool CInspectorProperty::GetReadOnly()
{
	return m_bReadOnly;
}
const CString& CInspectorProperty::GetName() const
{
	return m_name;
}
void CInspectorProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInspectorProperty, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CInpsectorProperty 消息处理程序

bool CInspectorProperty::Create(CWnd* pParent)
{
	m_pPanel = (CInspectorPanel*)pParent;
	m_bkBrush.CreateSolidBrush(RGB(70, 70, 70));
	return CDialogEx::Create(m_nIDD, pParent);
}
int CInspectorProperty::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;




	return 0;
}


void CInspectorProperty::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(rc);
	dc.FillRect(rc, &m_bkBrush);

	CDialogEx::OnPaint();
}


void CInspectorProperty::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	//Invalidate();
}


HBRUSH CInspectorProperty::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(200,200,200));
		pDC->SetBkColor(RGB(70, 70, 70));
	}
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		return hbr;
	}
	return m_bkBrush;
}


void CInspectorProperty::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	m_pPanel->SetFocus();
	//CDialogEx::OnOK();
}


void CInspectorProperty::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pPanel->SetFocus();
	//CDialogEx::OnCancel();
}


void CInspectorProperty::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}
void CInspectorProperty::SetUserData(void* pUserData)
{
	m_pUserData = pUserData;
}
void* CInspectorProperty::GetUserData()
{
	return m_pUserData;
}
void CInspectorProperty::OnValueChanged()
{
	m_pPanel->OnPropertyChanged(this);
}
ld3d::Property* CInspectorProperty::GetProperty()
{
	return m_pProp;
}
void CInspectorProperty::Hide()
{
	m_bVisible = false;
}
void CInspectorProperty::Show()
{
	m_bVisible = true;
}
bool CInspectorProperty::IsVisible()
{
	return m_bVisible;
}
CInspectorPanel* CInspectorProperty::GetPanel()
{
	return m_pPanel;
}