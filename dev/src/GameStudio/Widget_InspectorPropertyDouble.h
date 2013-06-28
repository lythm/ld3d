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

public slots:
	void								on_value_changed();
private:
	QLineEdit*							m_pValue;
};

