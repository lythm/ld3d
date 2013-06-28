#include "stdafx.h"
#include "Widget_InspectorPanelBar.h"


Widget_InspectorPanelBar::Widget_InspectorPanelBar(QWidget* parent, const QString& name)
	: QWidget(parent)
{
	m_pTitle = new QPushButton(name, this);
	m_pTitle->setFlat(true);
	connect(m_pTitle, SIGNAL(clicked()), this, SIGNAL(clicked()));
}


Widget_InspectorPanelBar::~Widget_InspectorPanelBar(void)
{
}
void Widget_InspectorPanelBar::resizeEvent(QResizeEvent* e)
{
	m_pTitle->setGeometry(0, 0, e->size().width(), 16);
	QWidget::resizeEvent(e);
}
QSize Widget_InspectorPanelBar::sizeHint() const
{
	return QSize(100, 17);
}
