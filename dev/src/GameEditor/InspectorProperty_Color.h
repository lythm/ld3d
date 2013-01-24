#pragma once

#include "InspectorProperty_Simple.h"


class CInspectorProperty_Color : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_Color(CString name);
	virtual ~CInspectorProperty_Color(void);
	virtual BOOL OnInitDialog();
};

