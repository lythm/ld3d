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
#include "Widget_InspectorPropertyPath.h"

Form_Inspector::Form_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	m_pInspector = new Widget_Inspector(this);

	inspector_layout->addWidget(m_pInspector);
	inspector_layout->addWidget(new QPushButton("Add Component", this));

	


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
			pProp = pPanel->AddPathProperty(QString::fromStdWString(p->getName()), ((StringProperty*)p)->Get());
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
		pProp->on_property_changed = std::bind(&Form_Inspector::on_property_changed, this, std::placeholders::_1);
	}
	return pProp;
}
void Form_Inspector::on_property_changed(Widget_InspectorProperty* prop)
{
	if(prop->GetUserData() == nullptr)
	{
		assert(0);
		return;
	}

	using namespace ld3d;
	switch(((Property*)(prop->GetUserData()))->getType())
	{
	case property_type_filepath:
		{
			FilePathProperty* p = (FilePathProperty*)prop->GetUserData();
			
			boost::filesystem::path  value = ((Widget_InspectorPropertyPath*)prop)->GetValue();
			p->Set(value);

			value = p->Get();
			((Widget_InspectorPropertyPath*)prop)->SetValue(value);
			
		}
		break;
	case property_type_matrix44:
		{
			Matrix44Property* p = (Matrix44Property*)prop->GetUserData();
			
			math::Matrix44  value = ((Widget_InspectorPropertyTransform*)prop)->GetValue();
			p->Set(value);

			value = p->Get();
			((Widget_InspectorPropertyTransform*)prop)->SetValue(value);
		}
		break;
	case property_type_string:
		{
			StringProperty* p = (StringProperty*)prop->GetUserData();
			QString value = ((Widget_InspectorPropertyString*)prop)->GetValue();
			p->Set(value.toStdWString());

			value = QString::fromStdWString(p->Get());
			((Widget_InspectorPropertyString*)prop)->SetValue(value);

		}
		break;
	case property_type_bool:
		{
			BoolProperty* p = (BoolProperty*)prop->GetUserData();
			
			bool  value = ((Widget_InspectorPropertyBool*)prop)->GetValue();
			p->Set(value);

			value = p->Get();
			((Widget_InspectorPropertyBool*)prop)->SetValue(value);


		}
		break;
	case property_type_int:
		{
			IntProperty* p = (IntProperty*)prop->GetUserData();
			
			int  value = ((Widget_InspectorPropertyInt*)prop)->GetValue();
			p->Set(value);

			value = p->Get();
			((Widget_InspectorPropertyInt*)prop)->SetValue(value);
		}
		break;
	case property_type_float:
		{
			FloatProperty* p = (FloatProperty*)prop->GetUserData();
			
			double  value = ((Widget_InspectorPropertyDouble*)prop)->GetValue();
			p->Set(float(value));

			value = p->Get();
			((Widget_InspectorPropertyDouble*)prop)->SetValue(value);

		}
		break;
	case property_type_color:
		{
			ColorProperty* p = (ColorProperty*)prop->GetUserData();
			
			QColor value = ((Widget_InspectorPropertyColor*)prop)->GetValue();

			p->Set(math::Color4(value.redF(), value.greenF(), value.blueF(), value.alphaF()));

			value = QColor::fromRgbF(p->Get().r, p->Get().g, p->Get().b, p->Get().a);
			((Widget_InspectorPropertyColor*)prop)->SetValue(value);

		}
		break;
	case property_type_signal:
		{
			//pProp = new CInspectorProperty_Signal(p->getName().c_str(), p);
		}
	default:
		break;

	}
}
