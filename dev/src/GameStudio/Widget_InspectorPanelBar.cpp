#include "stdafx.h"
#include "Widget_InspectorPanelBar.h"


Widget_InspectorPanelBar::Widget_InspectorPanelBar(QWidget* parent)
	: QWidget(parent)
{
	m_pTitle = new QLabel("Title Bar", this);

	setMinimumHeight(19);
}


Widget_InspectorPanelBar::~Widget_InspectorPanelBar(void)
{
}
void Widget_InspectorPanelBar::resizeEvent(QResizeEvent* e)
{
	m_pTitle->setGeometry(0, 0, e->size().width(), e->size().height());
	QWidget::resizeEvent(e);
}
