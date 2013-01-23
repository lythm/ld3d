#pragma once

#include "resource.h"

// CInpsectorProperty �Ի���

class CInspectorProperty : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectorProperty)

public:
	CInspectorProperty(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInspectorProperty();

// �Ի�������
	enum { IDD = IDD_INPSECTOR_PROPERTY };

	bool									Create(CWnd* pParent);

private:
	CBrush									m_bkBrush;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};
