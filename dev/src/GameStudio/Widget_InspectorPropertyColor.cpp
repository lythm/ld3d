#include "stdafx.h"
#include "Widget_InspectorPropertyColor.h"




Widget_InspectorPropertyColor::Widget_InspectorPropertyColor(QWidget *parent, const QString& name, const QColor& value)
	:Widget_InspectorPropertySimple(parent, name) , m_value(this, value)
{
	SetValueWidget(&m_value);
	SetValue(value);

	connect(&m_value, SIGNAL(colorChanged(const QColor&)), this, SLOT(on_value_changed(const QColor&)));
}

Widget_InspectorPropertyColor::~Widget_InspectorPropertyColor(void)
{
}
QColor Widget_InspectorPropertyColor::GetValue()
{
	return m_value.color();
}
void Widget_InspectorPropertyColor::SetValue(const QColor& value)
{
	m_value.setColor(value);
}

void Widget_InspectorPropertyColor::on_value_changed(const QColor&)
{
	on_property_changed ? on_property_changed(this) : 0;
}