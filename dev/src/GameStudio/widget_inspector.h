#ifndef WIDGET_INSPECTOR_H
#define WIDGET_INSPECTOR_H

#include <QWidget>
class Widget_InspectorProperty;

class Widget_Inspector : public QWidget
{
	Q_OBJECT

public:
	Widget_Inspector(QWidget *parent = 0);
	~Widget_Inspector();

private:
	void										resizeEvent(QResizeEvent* e);
private:
	Widget_InspectorProperty*					m_pProperty;
};

#endif // WIDGET_INSPECTOR_H
