#pragma once

#define INSPECTOR_CAPTION_HEIGHT				20
// CInspectorPanel �Ի���
class CInspectorCtrl;
class CInspectorProperty;

class CInspectorPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectorPanel)

public:
	CInspectorPanel(CInspectorCtrl* pCtrl);   // ��׼���캯��
	virtual ~CInspectorPanel();


	void										Fold();
	void										UnFold();

	int											GetHeight();

	bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);

	void										InvalidatePanel();
private:
	void										ShowProps();
private:
	CWnd*										m_pContentWnd;
	CBrush										m_bkBrush;
	CString										m_name;
	CInspectorCtrl*								m_pInspector;
	bool										m_bExpanded;

	std::vector<CInspectorProperty*>			m_propList;
// �Ի�������
	enum { IDD = IDD_INSPECTOR_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedName();

};
