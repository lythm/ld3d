#include "stdafx.h"
#include "Widget_InspectorPropertyDouble.h"



Widget_InspectorPropertyDouble::Widget_InspectorPropertyDouble(QWidget *parent, const QString& name, double value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new QLineEdit(this);
	m_pValue->setValidator(new QDoubleValidator);
	
	SetValueWidget(m_pValue);
	SetValue(value);

	connect(m_pValue, SIGNAL(editingFinished()), this, SLOT(on_value_changed()));

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
	m_pValue->setText(QString::number(value));
}

void Widget_InspectorPropertyDouble::on_value_changed()
{
	on_property_changed ? on_property_changed(this) : 0;
}