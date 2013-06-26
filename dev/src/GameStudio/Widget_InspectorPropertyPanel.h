#pragma once
#include "widget_inspectorproperty.h"

class Widget_InspectorPropertyPanel: public Widget_InspectorProperty
{
	Q_OBJECT
public:
	Widget_InspectorPropertyPanel(QWidget* parent, const QString& name = "Panel");
	virtual ~Widget_InspectorPropertyPanel(void);

	

private:
	
	std::vector<QWidget*>						m_props;
};

