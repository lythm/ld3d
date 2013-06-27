#include "stdafx.h"
#include "form_inspector.h"
#include "widget_inspector.h"
#include "Widget_InspectorPanel.h"
#include "widget_inspectorpropertystring.h"
#include "widget_inspectorpropertyint.h"
#include "widget_inspectorpropertydouble.h"
#include "Widget_InspectorPropertyBool.h"
#include "Widget_InspectorPropertyColor.h"
#include "Widget_InspectorPropertyTransform.h"
#include "Widget_InspectorPanel.h"


Form_Inspector::Form_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	

	//setStyleSheet("background-color:rgb(89,89,89);}");

	m_pInspector = new Widget_Inspector(this);
	
	inspector_layout->addWidget(m_pInspector);
	
	//inspector_layout->addWidget(new QPushButton(this));
	
	
}

Form_Inspector::~Form_Inspector()
{

}
void Form_Inspector::resizeEvent(QResizeEvent* e)
{
	QWidget::resizeEvent(e);
}
void Form_Inspector::SetObject(ld3d::GameObject* pObj)
{
	using namespace ld3d;

	m_pInspector->RemoveAll();

	if(pObj == nullptr)
	{
		return;
	}
	
	PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(pObj->GetComponent(L"PropertyManager"));
	
	for(int i = 0; i < pPM->GetPropertySetCount(); ++i)
	{
		PropertySetPtr pO = pPM->GetPropertySet(i);

		Widget_InspectorPanel* pPanel = m_pInspector->AddPanel(QString::fromStdWString(pO->getName()));

		for(size_t ii = 0; ii < pO->getPropertyCount(); ++ii)
		{
			Property* p = pO->getProperty(ii);
			Widget_InspectorProperty* pProp = AddProperty(pPanel, p);
		}
	}
}


Widget_InspectorProperty* Form_Inspector::AddProperty(Widget_InspectorPanel* pPanel, ld3d::Property* p)
{
	using namespace ld3d;

	Widget_InspectorProperty* pProp = nullptr;
	switch(p->getType())
	{
	case property_type_filepath:
		{
			//pProp = new CInspectorProperty_FilePath(p->getName().c_str(), p, false);
		}
		break;
	case property_type_matrix44:
		{
			math::Matrix44 v = ((Matrix44Property*)p)->Get();

			pProp = pPanel->AddTransformProperty(v);
			
		}
		break;
	case property_type_string:
		{
			pProp = pPanel->AddStringProperty(QString::fromStdWString(p->getName()), QString::fromStdWString(((StringProperty*)p)->Get()));
		}
		break;
	case property_type_bool:
		{
			pProp = pPanel->AddBoolProperty(QString::fromStdWString(p->getName()), ((BoolProperty*)p)->Get());
		}
		break;
	case property_type_int:
		{
			pProp = pPanel->AddIntProperty(QString::fromStdWString(p->getName()), ((IntProperty*)p)->Get());
			
		}
		break;
	case property_type_float:
		{
			pProp = pPanel->AddDoubleProperty(QString::fromStdWString(p->getName()), ((FloatProperty*)p)->Get());
		}
		break;
	case property_type_color:
		{
			math::Color4 clr = ((ColorProperty*)p)->Get();
			
			QColor value(clr.r * 255, clr.g * 255, clr.b * 255, clr.a * 255);
			pProp = pPanel->AddColorProperty(QString::fromStdWString(p->getName()), value);
		}
		break;
	case property_type_signal:
		{
			//pProp = new CInspectorProperty_Signal(p->getName().c_str(), p);
		}
	default:
		break;
	}
	if(pProp)
	{
		pProp->SetUserData(p);
	}
	return pProp;
}