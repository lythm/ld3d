#pragma once

#include "InspectorCtrl.h"

class CInspector : public CInspectorCtrl
{
public:
	CInspector(void);
	virtual ~CInspector(void);

	void							UpdateGameObjectProperty(ld3d::GameObjectPtr pObj);

	void							AddPropertySet(ld3d::PropertySetPtr pSet);
	void							OnPropertyChanged(CInspectorProperty* pProp);

	CInspectorProperty*				CreateProperty(ld3d::Property* p);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

