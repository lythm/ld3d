#pragma once

#include "InspectorProperty.h"

class CInspectorProperty_Simple : public CInspectorProperty
{
public:
	CInspectorProperty_Simple(CString name, UINT nIDD);
	virtual ~CInspectorProperty_Simple(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

