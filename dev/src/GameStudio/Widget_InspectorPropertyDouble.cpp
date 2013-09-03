#include "stdafx.h"
#include "Widget_InspectorPropertyDouble.h"



Widget_InspectorPropertyDouble::Widget_InspectorPropertyDouble(QWidget *parent, const QString& name, double value)
	:Widget_InspectorPropertySimple(parent, name), m_value(this)
{

	m_value.setValidator(&m_validator);
	
	SetValueWidget(&m_value);
	SetValue(value);

	connect(&m_value, SIGNAL(editingFinished()), this, SLOT(on_value_changed()));

}

Widget_InspectorPropertyDouble::~Widget_InspectorPropertyDouble(void)
{
}
double Widget_InspectorPropertyDouble::GetValue()
{
	return m_value.text().toDouble();
}
void Widget_InspectorPropertyDouble::SetValue(double value)
{
	m_value.setText(QString::number(value));
}

void Widget_InspectorPropertyDouble::on_value_changed()
{
	on_property_changed ? on_property_changed(this) : 0;
}