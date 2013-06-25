#include "stdafx.h"
#include "widget_inspectorpropertystring.h"

Widget_InspectorPropertyString::Widget_InspectorPropertyString(QWidget *parent, const QString& name, const QString& value)
	: Widget_InspectorPropertySimple(parent, name)
{
	m_pValue = new QLineEdit(this);
	SetValueWidget(m_pValue);
	m_pValue->setText(value);
}

Widget_InspectorPropertyString::~Widget_InspectorPropertyString()
{

}
QString	Widget_InspectorPropertyString::GetValue()
{
	return m_pValue->text();
}
void Widget_InspectorPropertyString::SetValue(const QString& value)
{
	m_pValue->setText(value);

	on_property_changed ? on_property_changed(this) : 0;
}
void Widget_InspectorPropertyString::FixValue(const QString& value)
{
	m_pValue->setText(value);
}
