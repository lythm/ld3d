#ifndef WIDGET_INSPECTORPROPERTYSTRING_H
#define WIDGET_INSPECTORPROPERTYSTRING_H

#include "widget_inspectorpropertysimple.h"

class Widget_InspectorPropertyString : public Widget_InspectorPropertySimple
{
	Q_OBJECT

public:
	Widget_InspectorPropertyString(QWidget *parent, const QString& name = "name", const QString& value = "");
	~Widget_InspectorPropertyString();
	
	QString								GetValue();
	void								SetValue(const QString& value);
	void								FixValue(const QString& value);
private:
	QLineEdit*							m_pValue;
};

#endif // WIDGET_INSPECTORPROPERTYSTRING_H
