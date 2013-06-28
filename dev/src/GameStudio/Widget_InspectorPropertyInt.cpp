#include "stdafx.h"
#include "Widget_InspectorPropertyInt.h"


Widget_InspectorPropertyInt::Widget_InspectorPropertyInt(QWidget *parent, const QString& name, int value)
	:Widget_InspectorPropertySimple(parent, name)
{

	m_pValue = new QLineEdit(this);
	m_pValue->setValidator(new QIntValidator);
	
	SetValueWidget(m_pValue);
	SetValue(value);

	connect(m_pValue, SIGNAL(editingFinished()), this, SLOT(on_value_changed()));

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
	m_pValue->setText(QString::number(value));
}
void Widget_InspectorPropertyInt::on_value_changed()
{
	on_property_changed ? on_property_changed(this) : 0;
}