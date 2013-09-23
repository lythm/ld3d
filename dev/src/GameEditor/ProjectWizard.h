#pragma once

#include "resource.h"
#include "afxcmn.h"

// CProjectWizard �Ի���

class CProjectWizard : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectWizard)

public:
	CProjectWizard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProjectWizard();

// �Ի�������
	enum { IDD = IDD_PROJECT_NEW_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedPwButtonNew();
	afx_msg void OnBnClickedPwButtonOpen();
};
