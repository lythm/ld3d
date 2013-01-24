#pragma once

#include "InspectorProperty_Simple.h"

class CInspectorProperty_Float : public CInspectorProperty_Simple
{
	
public:
	enum { IDD = IDD_INSPECTOR_PROPERTY_FLOAT, };

	CInspectorProperty_Float(CString name);
	virtual ~CInspectorProperty_Float(void);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	double m_value;
	virtual BOOL OnInitDialog();
};

