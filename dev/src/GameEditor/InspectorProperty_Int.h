#pragma once

#include "InspectorProperty_Simple.h"


class CInspectorProperty_Int : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_Int(CString name);
	virtual ~CInspectorProperty_Int(void);


	int									GetValue() const;
	void								SetValue(int v);

private:
	void								ProcessInput();
private:
	int									m_value;
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeValue();
	afx_msg void OnEnUpdateValue();
};

