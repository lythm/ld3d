
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList ����


class COutputEdit : public CEdit
{
public:
	COutputEdit();
	virtual ~COutputEdit();

	BOOL Create(const RECT& rect, CWnd* pParentWnd);
	void					AddLine(const CString& l);
	void					ScrollToEnd();

protected:
	
	CString					Format(const CString& l);

private:
	CString					m_buffer;
	
	
public:
	afx_msg void OnOutputEditSelectAll();
	afx_msg void OnViewOutput();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();

	DECLARE_MESSAGE_MAP()
};



class COutputWnd : public CDockablePane
{
// ����
public:
	COutputWnd();

	void			UpdateFonts();

	void			OuputInfo(const CString& string);
	void			OuputBuild(const CString& string);
// ����
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputEdit m_wndOutputMessage;
	COutputEdit m_wndOutputBuild;

protected:

// ʵ��
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	
};

