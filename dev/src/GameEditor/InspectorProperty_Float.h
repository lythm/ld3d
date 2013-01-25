#pragma once

#include "InspectorProperty_Simple.h"
#include "afxwin.h"
#include "FloatEdit.h"
class CInspectorProperty_Float : public CInspectorProperty_Simple
{
	
public:
	enum { IDD = IDD_INSPECTOR_PROPERTY_FLOAT, };

	CInspectorProperty_Float(CString name, float value, void* pUserData = nullptr);
	virtual ~CInspectorProperty_Float(void);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	float									GetValue();
	void									SetValue(float v);
		
private:

	DECLARE_MESSAGE_MAP()
//	double m_value;
	virtual BOOL OnInitDialog();
	CFloatEdit m_value;
	float m_initValue;
	afx_msg void OnEnKillfocusValue();
};

