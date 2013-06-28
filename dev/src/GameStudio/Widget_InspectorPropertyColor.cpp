#include "stdafx.h"
#include "Widget_InspectorPropertyColor.h"




Widget_InspectorPropertyColor::Widget_InspectorPropertyColor(QWidget *parent, const QString& name, const QColor& value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new Widget_ColorButton(this, value);
	
	SetValueWidget(m_pValue);
	SetValue(value);

	connect(m_pValue, SIGNAL(colorChanged(const QColor&)), this, SLOT(on_value_changed(const QColor&)));
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
	m_pValue->setColor(value);
}

void Widget_InspectorPropertyColor::on_value_changed(const QColor&)
{
	on_property_changed ? on_property_changed(this) : 0;
}