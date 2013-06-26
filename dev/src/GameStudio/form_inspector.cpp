#include "stdafx.h"
#include "form_inspector.h"
#include "widget_inspector.h"

Form_Inspector::Form_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	
	m_pInspector = new Widget_Inspector(this);
	
	inspector_layout->addWidget(m_pInspector);
	
	inspector_layout->addWidget(new QPushButton(this));

	for(int i = 0; i < 10; ++i)
	{
		m_pInspector->AddTransformProperty(math::MatrixIdentity());
		m_pInspector->AddStringProperty("Name", "Tom");
		m_pInspector->AddIntProperty("Age", 30);
		m_pInspector->AddDoubleProperty("Weight", 59.5);
		m_pInspector->AddBoolProperty("Married", false);
		m_pInspector->AddColorProperty("Favorate Color", QColor(180, 200, 55));
		
	}
}

Form_Inspector::~Form_Inspector()
{

}
void Form_Inspector::resizeEvent(QResizeEvent* e)
{
	QWidget::resizeEvent(e);
}
void Form_Inspector::SetObject(ld3d::GameObjectPtr pObj)
{

}
