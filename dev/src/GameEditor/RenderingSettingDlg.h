#pragma once


// CRenderingSettingDlg �Ի���

class CRenderingSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRenderingSettingDlg)

public:
	CRenderingSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRenderingSettingDlg();

// �Ի�������
	enum { IDD = IDD_RENDERING_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
