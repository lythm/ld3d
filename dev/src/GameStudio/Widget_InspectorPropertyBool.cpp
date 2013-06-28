#include "stdafx.h"
#include "Widget_InspectorPropertyBool.h"




Widget_InspectorPropertyBool::Widget_InspectorPropertyBool(QWidget *parent, const QString& name, bool value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new QCheckBox(this);
	
	SetValueWidget(m_pValue);
	SetValue(value);

	connect(m_pValue, SIGNAL(stateChanged(int)), this, SLOT(on_value_changed(int)));
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
	m_pValue->setChecked(value);
}

void Widget_InspectorPropertyBool::on_value_changed(int)
{
	on_property_changed ? on_property_changed (this) : 0;
}