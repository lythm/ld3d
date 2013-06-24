#include "stdafx.h"
#include "form_inspector.h"
#include "widget_inspector.h"

Form_Inspector::Form_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	

	m_pInspector = new Widget_Inspector(this);
	
	inspector_layout->addWidget(m_pInspector);

}

Form_Inspector::~Form_Inspector()
{

}
void Form_Inspector::resizeEvent(QResizeEvent* e)
{
	QWidget::resizeEvent(e);
}
