#pragma once


// CPreviewWnd �Ի���

class CPreviewWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CPreviewWnd)

public:
	CPreviewWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPreviewWnd();

// �Ի�������
	enum { IDD = IDD_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();


private:
	ld3d::RenderTargetPtr				m_pRenderTarget;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
