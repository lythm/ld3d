#pragma once

#include "InspectorProperty.h"

class CInspectorProperty_Signal : public CInspectorProperty
{
public:
	CInspectorProperty_Signal(CString name, ld3d::Property* pProp);
	virtual ~CInspectorProperty_Signal(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();



private:
	ld3d::Property*							m_pProp;
public:
	afx_msg void OnSignalBtn();
};

