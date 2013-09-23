#pragma once

#include "InspectorProperty_Simple.h"
#include "afxwin.h"
#include "IntEdit.h"


class CInspectorProperty_Int : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_Int(CString name, ld3d::Property* pProp, void* pUserData = nullptr);
	virtual ~CInspectorProperty_Int(void);


	int									GetValue() const;
	void								SetValue(int v);
	enum { IDD = IDD_INSPECTOR_PROPERTY_INT };
private:
	

private:

	CIntEdit m_valueEdit;
	int		m_oriValue;

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeValue();
	afx_msg void OnEnUpdateValue();
	
	afx_msg void OnEnKillfocusValue();
	
};

