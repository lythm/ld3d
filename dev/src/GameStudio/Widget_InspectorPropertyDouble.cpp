#include "stdafx.h"
#include "Widget_InspectorPropertyDouble.h"



Widget_InspectorPropertyDouble::Widget_InspectorPropertyDouble(QWidget *parent, const QString& name, double value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new QLineEdit(this);
	m_pValue->setValidator(new QDoubleValidator);
	
	SetValueWidget(m_pValue);
	SetValue(value);
}

Widget_InspectorPropertyDouble::~Widget_InspectorPropertyDouble(void)
{
}
double Widget_InspectorPropertyDouble::GetValue()
{
	return m_pValue->text().toDouble();
}
void Widget_InspectorPropertyDouble::SetValue(double value)
{
	FixValue(value);
	on_property_changed ? on_property_changed(this) : 0;
}
void Widget_InspectorPropertyDouble::FixValue(double value)
{
	m_pValue->setText(QString::number(value));
}
