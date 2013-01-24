#pragma once

#include "InspectorProperty_Simple.h"

class CInspectorProperty_String : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_String(CString name);
	virtual ~CInspectorProperty_String(void);
	virtual BOOL OnInitDialog();

	int									GetValue() const;
	void								SetValue(int v);

private:
	CString								m_value;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeValue();
};

