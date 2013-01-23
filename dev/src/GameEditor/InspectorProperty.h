#pragma once

#include "resource.h"

// CInpsectorProperty 对话框

class CInspectorProperty : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectorProperty)

public:
	CInspectorProperty(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInspectorProperty();

// 对话框数据
	enum { IDD = IDD_INPSECTOR_PROPERTY };

	bool									Create(CWnd* pParent);

private:
	CBrush									m_bkBrush;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};
