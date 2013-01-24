#pragma once

#include "InspectorProperty_Simple.h"

class CInspectorProperty_FilePath : public CInspectorProperty_Simple
{
public:
	CInspectorProperty_FilePath(CString name);
	virtual ~CInspectorProperty_FilePath(void);
	virtual BOOL OnInitDialog();
};

