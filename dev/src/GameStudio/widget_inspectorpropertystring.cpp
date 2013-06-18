#include "stdafx.h"
#include "widget_inspectorpropertystring.h"

Widget_InspectorPropertyString::Widget_InspectorPropertyString(QWidget *parent)
	: Widget_InspectorProperty(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	m_pName = new QLabel(this);
	m_pValue = new QLineEdit(this);

	QSize size = m_pName->size();
	size.setWidth(100);
	m_pName->resize(size);
	m_pName->setText("Label");
	m_pValue->move(50, 0);
	m_pValue->raise();

	
	
}

Widget_InspectorPropertyString::~Widget_InspectorPropertyString()
{

}
void Widget_InspectorPropertyString::resizeEvent(QResizeEvent* e)
{
	

	Widget_InspectorProperty::resizeEvent(e);
}