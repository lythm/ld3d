#include "stdafx.h"
#include "Widget_InspectorPropertyInt.h"


Widget_InspectorPropertyInt::Widget_InspectorPropertyInt(QWidget *parent, const QString& name, int value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new QLineEdit(this);
	m_pValue->setValidator(new QIntValidator);
	
	SetValueWidget(m_pValue);
	SetValue(value);
}

Widget_InspectorPropertyInt::~Widget_InspectorPropertyInt(void)
{
}
int Widget_InspectorPropertyInt::GetValue()
{
	return m_pValue->text().toInt();
}
void Widget_InspectorPropertyInt::SetValue(int value)
{
	FixValue(value);
	on_property_changed ? on_property_changed(this) : 0;
}
void Widget_InspectorPropertyInt::FixValue(int value)
{
	m_pValue->setText(QString::number(value));
}