#ifndef WIDGET_INSPECTORPROPERTYSIMPLE_H
#define WIDGET_INSPECTORPROPERTYSIMPLE_H

#include "widget_inspectorproperty.h"


class Widget_InspectorPropertySimple : public Widget_InspectorProperty
{
	Q_OBJECT

public:
	Widget_InspectorPropertySimple(QWidget *parent, const QString& name = "name", void* userData = nullptr);
	~Widget_InspectorPropertySimple();


	virtual void								resizeEvent(QResizeEvent* e);
	void										SetName(const QString& name);
	QString										GetName();

	QSize										sizeHint() const;
protected:
	void										SetValueWidget(QWidget* pValue);

private:
	QLabel*										m_pNameWidget;
	QWidget*									m_pValueWidget;
};

#endif // WIDGET_INSPECTORPROPERTYSIMPLE_H
