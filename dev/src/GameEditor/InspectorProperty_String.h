#pragma once

#include "InspectorProperty_Simple.h"

class CInspectorProperty_String : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_String(CString name, CString value, void* pUserData = nullptr);
	virtual ~CInspectorProperty_String(void);
	virtual BOOL OnInitDialog();

	CString								GetValue() const;
	void								SetValue(CString v);
	enum { IDD = IDD_INSPECTOR_PROPERTY_STRING };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
private:

	CString								m_value;
	CEdit								m_edit;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeValue();
	afx_msg void OnEnKillfocusValue();
	
};

