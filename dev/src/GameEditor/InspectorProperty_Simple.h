#pragma once

#include "InspectorProperty.h"

class CInspectorProperty_Simple : public CInspectorProperty
{
public:
	CInspectorProperty_Simple(CString name, ld3d::Property* pProp, void* pUserData = nullptr, UINT nIDD = IDD_INPSECTOR_PROPERTY);
	virtual ~CInspectorProperty_Simple(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

