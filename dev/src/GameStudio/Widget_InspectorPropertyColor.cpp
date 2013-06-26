#include "stdafx.h"
#include "Widget_InspectorPropertyColor.h"




Widget_InspectorPropertyColor::Widget_InspectorPropertyColor(QWidget *parent, const QString& name, const QColor& value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new Widget_ColorButton(this, value);
	
	SetValueWidget(m_pValue);
	SetValue(value);
}

Widget_InspectorPropertyColor::~Widget_InspectorPropertyColor(void)
{
}
QColor Widget_InspectorPropertyColor::GetValue()
{
	return m_pValue->color();
}
void Widget_InspectorPropertyColor::SetValue(const QColor& value)
{
	FixValue(value);
	on_property_changed ? on_property_changed(this) : 0;
}
void Widget_InspectorPropertyColor::FixValue(const QColor& value)
{
	m_pValue->setColor(value);
}
