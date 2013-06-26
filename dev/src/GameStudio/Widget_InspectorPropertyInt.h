#pragma once

#include "widget_inspectorpropertysimple.h"

class Widget_InspectorPropertyInt : public Widget_InspectorPropertySimple
{
	Q_OBJECT
public:
	Widget_InspectorPropertyInt(QWidget *parent, const QString& name = "name", int value = 0);
	virtual ~Widget_InspectorPropertyInt(void);


	int									GetValue();
	void								SetValue(int value);
	void								FixValue(int value);
private:
	QLineEdit*							m_pValue;
};

