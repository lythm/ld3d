#pragma once

#include "InspectorCtrl.h"

class CInspector : public CInspectorCtrl
{
public:
	CInspector(void);
	virtual ~CInspector(void);

	void							UpdateGameObjectProperty(ld3d::GameObjectPtr pObj);

	void							ShowProperty(const std::wstring& set, const std::wstring& name);

private:
	void							AddPropertySet(ld3d::PropertySetPtr pSet);
	void							OnPropertyChanged(CInspectorProperty* pProp);

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

