#include "stdafx.h"
#include "form_inspector.h"
#include "widget_inspector.h"

Form_Inspector::Form_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	m_pInspector = new Widget_Inspector(this);

}

Form_Inspector::~Form_Inspector()
{

}
