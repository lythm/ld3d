#ifndef WIDGET_INSPECTORPROPERTY_H
#define WIDGET_INSPECTORPROPERTY_H

#include <QWidget>

class Widget_InspectorProperty : public QWidget
{
	Q_OBJECT

public:
	Widget_InspectorProperty(QWidget *parent);
	~Widget_InspectorProperty();


	void										resizeEvent(QResizeEvent* e);

private:
	
};

#endif // WIDGET_INSPECTORPROPERTY_H
