#include "stdafx.h"
#include "widget_inspectorproperty.h"

Widget_InspectorProperty::Widget_InspectorProperty(QWidget *parent, void* userData)
	: QWidget(parent)
{
	m_pUserData = userData;

	//setStyleSheet("background-color:rgb(56,56,56);}");
}

Widget_InspectorProperty::~Widget_InspectorProperty()
{

}
void Widget_InspectorProperty::resizeEvent(QResizeEvent* e)
{
	QWidget::resizeEvent(e);
}
void Widget_InspectorProperty::SetUserData(void* data)
{
	m_pUserData = data;
}
void* Widget_InspectorProperty::GetUserData()
{
	return m_pUserData;
}
