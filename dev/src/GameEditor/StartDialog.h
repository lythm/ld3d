#pragma once

#include "resource.h"

// CStartDialog �Ի���

class CStartDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStartDialog)

public:
	CStartDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStartDialog();

// �Ի�������
	enum { IDD = IDD_STARTUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
