#pragma once

#include "resource.h"

// CInpsectorProperty �Ի���
class CInspectorPanel;
class CInspectorProperty : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectorProperty)

public:
	CInspectorProperty(CString name, void* pUserData = nullptr, UINT nIDD = IDD_INPSECTOR_PROPERTY);   // ��׼���캯��
	virtual ~CInspectorProperty();

// �Ի�������
	bool									Create(CWnd* pParent);
	const CString&							GetName() const;

	virtual void							OnValueChanged();

	void									SetUserData(void* pUserData);
	void*									GetUserData();

	virtual void							SetReadOnly(bool bReadOnly);
	virtual bool							GetReadOnly();

	virtual int								GetHeight(){return INSPECTOR_PROPERTY_ROW_HEIGHT + 1;}
private:
	CBrush									m_bkBrush;
	UINT									m_nIDD;
	CInspectorPanel*						m_pPanel;
	CString									m_name;
	void*									m_pUserData;
	bool									m_bReadOnly;
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
