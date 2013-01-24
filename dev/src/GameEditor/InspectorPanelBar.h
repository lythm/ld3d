#pragma once


// CInspectorPanelBar �Ի���
class CInspectorPanel;

class CInspectorPanelBar : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectorPanelBar)

public:
	CInspectorPanelBar(CString name);   // ��׼���캯��
	virtual ~CInspectorPanelBar();

// �Ի�������
	enum { IDD = IDD_INSPECTOR_PANEL };

	bool										Create(CInspectorPanel* pPanel);

private:
	CInspectorPanel*							m_pPanel;
	CBrush										m_bkBrush;
	CString										m_name;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedName();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
