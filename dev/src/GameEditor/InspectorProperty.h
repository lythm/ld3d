#pragma once

#include "resource.h"

// CInpsectorProperty �Ի���
class CInspectorPanel;
class CInspectorProperty : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectorProperty)
	static const int								H_PADDING = 4;
	static const int								V_PADDING = 2;
public:
	CInspectorProperty(CString name, UINT nIDD = IDD_INPSECTOR_PROPERTY);   // ��׼���캯��
	virtual ~CInspectorProperty();

// �Ի�������
	bool									Create(CWnd* pParent);
	const CString&							GetName() const;
private:
	CBrush									m_bkBrush;
	UINT									m_nIDD;
	CInspectorPanel*						m_pPanel;
	CString									m_name;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
