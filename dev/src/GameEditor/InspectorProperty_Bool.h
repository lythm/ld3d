#pragma once

#include "InspectorProperty_Simple.h"
#include "afxwin.h"

class CInspectorProperty_Bool : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_Bool(CString name, bool value, void* pUserData = nullptr);
	virtual ~CInspectorProperty_Bool(void);


	bool								GetValue();
	void								SetValue(bool v);

	enum { IDD = IDD_INSPECTOR_PROPERTY_BOOL };
private:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	
private:
	bool								m_value;
	CButton								m_valueButton;
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedValue();
};

