#pragma once

#include "resource.h"
// CAppSettingsDlg �Ի���

class CAppSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAppSettingsDlg)

public:
	CAppSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppSettingsDlg();

// �Ի�������
	enum { IDD = IDD_APPSETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
};
