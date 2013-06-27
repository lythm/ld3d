#include "stdafx.h"
#include "Widget_InspectorPanelBar.h"


Widget_InspectorPanelBar::Widget_InspectorPanelBar(QWidget* parent)
	: QWidget(parent)
{
	//setStyleSheet("background-color:rgb(56,56,56);}");

	m_pTitle = new QPushButton("Title Bar", this);
	//m_pTitle->setStyleSheet("background-color:rgb(56,56,56);}");
	setMinimumHeight(19);

	connect(m_pTitle, SIGNAL(clicked()), this, SIGNAL(clicked()));
}


Widget_InspectorPanelBar::~Widget_InspectorPanelBar(void)
{
}
void Widget_InspectorPanelBar::resizeEvent(QResizeEvent* e)
{
	m_pTitle->setGeometry(0, 0, e->size().width(), e->size().height());
	QWidget::resizeEvent(e);
}
QSize Widget_InspectorPanelBar::sizeHint() const
{
	return QSize(100, 19);
}
