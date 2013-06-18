#ifndef WIDGET_INSPECTORPROPERTYSTRING_H
#define WIDGET_INSPECTORPROPERTYSTRING_H

#include "widget_inspectorproperty.h"

class Widget_InspectorPropertyString : public Widget_InspectorProperty
{
	Q_OBJECT

public:
	Widget_InspectorPropertyString(QWidget *parent);
	~Widget_InspectorPropertyString();

private:
	void										resizeEvent(QResizeEvent* e);


private:

	QLabel*								m_pName;
	QLineEdit*							m_pValue;
};

#endif // WIDGET_INSPECTORPROPERTYSTRING_H
