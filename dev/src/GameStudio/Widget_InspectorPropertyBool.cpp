#include "stdafx.h"
#include "Widget_InspectorPropertyBool.h"




Widget_InspectorPropertyBool::Widget_InspectorPropertyBool(QWidget *parent, const QString& name, bool value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_value.setParent(this);
	
	SetValueWidget(&m_value);
	SetValue(value);

	connect(&m_value, SIGNAL(stateChanged(int)), this, SLOT(on_value_changed(int)));
}

Widget_InspectorPropertyBool::~Widget_InspectorPropertyBool(void)
{
}
bool Widget_InspectorPropertyBool::GetValue()
{
	return m_value.isChecked();
}
void Widget_InspectorPropertyBool::SetValue(bool value)
{
	m_value.setChecked(value);
}

void Widget_InspectorPropertyBool::on_value_changed(int)
{
	on_property_changed ? on_property_changed (this) : 0;
}