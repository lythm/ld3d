#include "stdafx.h"
#include "widget_inspector.h"
#include "widget_inspectorpropertystring.h"

Widget_Inspector::Widget_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	m_pProperty = new Widget_InspectorPropertyString(this);

	resize(800, 100);
}

Widget_Inspector::~Widget_Inspector()
{

}
void Widget_Inspector::resizeEvent(QResizeEvent* e)
{
	QWidget::resizeEvent(e);
}