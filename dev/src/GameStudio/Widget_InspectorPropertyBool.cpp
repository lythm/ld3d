#include "stdafx.h"
#include "Widget_InspectorPropertyBool.h"




Widget_InspectorPropertyBool::Widget_InspectorPropertyBool(QWidget *parent, const QString& name, bool value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new QCheckBox(this);
	
	SetValueWidget(m_pValue);
	SetValue(value);
}

Widget_InspectorPropertyBool::~Widget_InspectorPropertyBool(void)
{
}
bool Widget_InspectorPropertyBool::GetValue()
{
	return m_pValue->isChecked();
}
void Widget_InspectorPropertyBool::SetValue(bool value)
{
	FixValue(value);
	on_property_changed ? on_property_changed(this) : 0;
}
void Widget_InspectorPropertyBool::FixValue(bool value)
{
	m_pValue->setChecked(value);
}
