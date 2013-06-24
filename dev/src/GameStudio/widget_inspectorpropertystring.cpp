#include "stdafx.h"
#include "widget_inspectorpropertystring.h"

Widget_InspectorPropertyString::Widget_InspectorPropertyString(QWidget *parent)
	: Widget_InspectorProperty(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	m_pName = new QLabel(this);
	m_pValue = new QLineEdit(this);

	m_pName->setText("Name");
	m_pValue->move(200, 0);
}

Widget_InspectorPropertyString::~Widget_InspectorPropertyString()
{

}
void Widget_InspectorPropertyString::resizeEvent(QResizeEvent* e)
{
	

	Widget_InspectorProperty::resizeEvent(e);
}