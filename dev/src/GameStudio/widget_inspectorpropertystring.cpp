#include "stdafx.h"
#include "widget_inspectorpropertystring.h"

Widget_InspectorPropertyString::Widget_InspectorPropertyString(QWidget *parent, const QString& name, const QString& value)
	: Widget_InspectorPropertySimple(parent, name)
{
	m_value.setParent(this);

	//m_pValue = new QLineEdit(this);
	SetValueWidget(&m_value);
	m_value.setText(value);

	connect(&m_value, SIGNAL(editingFinished()), this, SLOT(slotTextChanged()));
}

Widget_InspectorPropertyString::~Widget_InspectorPropertyString()
{

}
QString	Widget_InspectorPropertyString::GetValue()
{
	return m_value.text();
}
void Widget_InspectorPropertyString::SetValue(const QString& value)
{
	m_value.setText(value);
}
void Widget_InspectorPropertyString::slotTextChanged()
{
	on_property_changed ? on_property_changed(this) : 0;
}
