#include "stdafx.h"
#include "Inspector.h"
#include "InspectorProperty_Int.h"
#include "InspectorProperty_String.h"
#include "InspectorProperty_Color.h"
#include "InspectorProperty_Float.h"
#include "InspectorProperty_Bool.h"
#include "InspectorProperty_FilePath.h"
#include "InspectorProperty_Range.h"
#include "InspectorProperty_Transform.h"
#include "InspectorProperty_Signal.h"
#include "InspectorPanel.h"

#include "editor_utils.h"

#include "Project.h"


CInspector::CInspector(void)
{
}


CInspector::~CInspector(void)
{
}
void CInspector::UpdateGameObjectProperty(ld3d::GameObjectPtr pObj)
{
	using namespace ld3d;

	RemoveAll();

	if(pObj == nullptr)
	{
		Invalidate();
		
		return;
	}
	
	PropertyManagerPtr pPM = boost::dynamic_pointer_cast<PropertyManager>(pObj->GetComponent(L"PropertyManager"));
	
	for(int i = 0; i < pPM->GetPropertySetCount(); ++i)
	{
		PropertySetPtr pO = pPM->GetPropertySet(i);

		AddPropertySet(pO);
	}

	Invalidate();
}
void CInspector::AddPropertySet(ld3d::PropertySetPtr pSet)
{
	using namespace ld3d;

	if(pSet == nullptr)
	{
		return;
	}

	CInspectorPanel* pPanel = new CInspectorPanel(pSet->getName().c_str(), pSet);

	AddPanel(pPanel);
	
}

BEGIN_MESSAGE_MAP(CInspector, CInspectorCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CInspector::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CInspectorCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
void CInspector::OnPropertyChanged(CInspectorProperty* pProp)
{
	
	//util_update_object_view(Project::Instance()->Root());
}
void CInspector::ShowProperty(const std::wstring& set, const std::wstring& name)
{

}