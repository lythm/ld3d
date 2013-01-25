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
#include "InspectorPanel.h"

#include "editor_utils.h"

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

	using namespace ld3d;

	PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(pObj->GetComponent(L"PropertyManager"));
	
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

	CInspectorPanel* pPanel = new CInspectorPanel(pSet->getName().c_str());

	for(size_t ii = 0; ii < pSet->getPropertyCount(); ++ii)
	{
		Property* p = pSet->getProperty(ii);
		CInspectorProperty* pSub = CreateProperty(p);

		pPanel->AddProperty(pSub);
	}

	AddPanel(pPanel);
	
}

CInspectorProperty* CInspector::CreateProperty(ld3d::Property* p)
{
	using namespace ld3d;

	CInspectorProperty* pProp = nullptr;
	switch(p->getType())
	{
	case property_type_matrix44:
		{
			const math::Matrix44 v = ((Matrix44Property*)p)->Get();

			pProp = new CInspectorProperty_Transform(p->getName().c_str(), v, p);
			
			if(((Matrix44Property*)p)->IsReadOnly())
			{
				pProp->SetReadOnly(true);
			}
		}
		break;
	case property_type_string:
		{
			std::wstring v = ((StringProperty*)p)->Get();

			pProp = new CInspectorProperty_String(p->getName().c_str(), v.c_str(), p);

			if(((StringProperty*)p)->IsReadOnly())
			{
				pProp->SetReadOnly(true);
			}
		}
		break;
	case property_type_bool:
		{
			bool v = ((BoolProperty*)p)->Get();

			pProp = new CInspectorProperty_Bool(p->getName().c_str(), v, p);

			if(((BoolProperty*)p)->IsReadOnly())
			{
				pProp->SetReadOnly(true);
			}
		}
		break;
	case property_type_int:
		{
			int v = ((IntProperty*)p)->Get();

			pProp = new CInspectorProperty_Int(p->getName().c_str(), v, p);
			
			if(((IntProperty*)p)->IsReadOnly())
			{
				pProp->SetReadOnly(true);
			}
		}
		break;
	case property_type_float:
		{
			float v = ((FloatProperty*)p)->Get();

			pProp = new CInspectorProperty_Float(p->getName().c_str(), v, p);
			
			if(((FloatProperty*)p)->IsReadOnly())
			{
				pProp->SetReadOnly(true);
			}
		}
		break;
	case property_type_color:
		{
			math::Color4 v = ((ColorProperty*)p)->Get();

			COLORREF c = RGB(v.r * 255, v.g * 255, v.b * 255);

			pProp = new CInspectorProperty_Color(p->getName().c_str(), v, p);
			if(((ColorProperty*)p)->IsReadOnly())
			{
				pProp->SetReadOnly(true);
			}
		}
		break;
	default:
		break;
	}
	
	return pProp;
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
	using namespace ld3d;
	Property* p = (Property*)pProp->GetUserData();

	switch(p->getType())
	{
	case property_type_string:
		{
			CInspectorProperty_String* pStrProp = (CInspectorProperty_String*)pProp;

			((StringProperty*)p)->Set(pStrProp->GetValue().GetString());
		}
		break;
	case property_type_bool:
		{
			CInspectorProperty_Bool* pBoolProp = (CInspectorProperty_Bool*)pProp;
			((BoolProperty*)p)->Set(pBoolProp->GetValue());

		}
		break;
	case property_type_matrix44:
		{
			CInspectorProperty_Transform* pTMProp =(CInspectorProperty_Transform*)pProp;

			((Matrix44Property*)p)->Set(pTMProp->GetValue());

		}
		break;
	case property_type_int:
		{
			CInspectorProperty_Int* pIntProp =(CInspectorProperty_Int*)pProp;

			((IntProperty*)p)->Set(pIntProp->GetValue());
		}
		break;
	case property_type_float:
		{
			CInspectorProperty_Float* pFloatProp = (CInspectorProperty_Float*)pProp;

			((FloatProperty*)p)->Set(pFloatProp->GetValue());
			pFloatProp->SetValue(((FloatProperty*)p)->Get());
		}
		break;
	case property_type_color:
		{

			CInspectorProperty_Color* pColorProp = (CInspectorProperty_Color*)pProp;

			((ColorProperty*)p)->Set(pColorProp->GetValue());

		}
		break;
	default:
		break;
	}
}
