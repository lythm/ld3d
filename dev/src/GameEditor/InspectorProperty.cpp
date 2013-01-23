// InpsectorProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "InspectorProperty.h"
#include "afxdialogex.h"



// CInpsectorProperty 对话框

IMPLEMENT_DYNAMIC(CInspectorProperty, CDialogEx)

CInspectorProperty::CInspectorProperty(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInspectorProperty::IDD, pParent)
{

}

CInspectorProperty::~CInspectorProperty()
{
	m_bkBrush.DeleteObject();
}

void CInspectorProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInspectorProperty, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInpsectorProperty 消息处理程序

bool CInspectorProperty::Create(CWnd* pParent)
{
	m_bkBrush.CreateSolidBrush(RGB(70, 70, 70));
	return CDialogEx::Create(IDD, pParent);
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
