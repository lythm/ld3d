#pragma once

#include "widget_inspectorpropertysimple.h"
#include "Widget_ColorButton.h"

class Widget_InspectorPropertyColor : public Widget_InspectorPropertySimple
{
public:
	Q_OBJECT
public:
	Widget_InspectorPropertyColor(QWidget *parent, const QString& name = "name", const QColor& value = QColor(255, 255, 255));
	virtual ~Widget_InspectorPropertyColor(void);


	QColor								GetValue();
	void								SetValue(const QColor& value);
	void								FixValue(const QColor& value);
private:
	Widget_ColorButton*					m_pValue;

};

