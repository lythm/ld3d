#pragma once
#include "widget_inspectorpropertysimple.h"


class Widget_InspectorPropertyDouble : public Widget_InspectorPropertySimple
{
public:
	Q_OBJECT
public:
	Widget_InspectorPropertyDouble(QWidget *parent, const QString& name = "name", double value = 0);
	virtual ~Widget_InspectorPropertyDouble(void);


	double								GetValue();
	void								SetValue(double value);
	void								FixValue(double value);
private:
	QLineEdit*							m_pValue;
};

