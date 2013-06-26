#include "stdafx.h"
#include "form_inspector.h"
#include "widget_inspector.h"
#include "Widget_InspectorPanel.h"

Form_Inspector::Form_Inspector(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	
	m_pInspector = new Widget_Inspector(this);
	
	inspector_layout->addWidget(m_pInspector);
	
	inspector_layout->addWidget(new QPushButton(this));

	


	for(int i = 0; i < 2; ++i)
	{
		Widget_InspectorPanel* pPanel = m_pInspector->AddPanel();
		
		pPanel->AddTransformProperty(math::MatrixIdentity());
		pPanel->AddStringProperty("Name", "Tom");
		pPanel->AddIntProperty("Age", 30);
		pPanel->AddDoubleProperty("Weight", 59.5);

		pPanel = pPanel->AddPanel();

		pPanel->AddBoolProperty("Married", false);
		pPanel->AddColorProperty("Favorate Color", QColor(180, 200, 55));
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
