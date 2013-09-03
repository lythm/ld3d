#ifndef FORM_INSPECTOR_H
#define FORM_INSPECTOR_H

#include <QWidget>
#include "ui_form_inspector.h"

class Widget_Inspector;
class Widget_InspectorProperty;
class Widget_InspectorPanel;
class Form_Inspector : public QWidget, public Ui::Form_Inspector
{
	Q_OBJECT

public:
	Form_Inspector(QWidget *parent = 0);
	~Form_Inspector();


	void									SetObject(ld3d::GameObject* pObj);
private:
	void									resizeEvent(QResizeEvent* e);
	Widget_InspectorProperty*				AddProperty(Widget_InspectorPanel* pPanel, ld3d::Property* p);

	void									on_property_changed(Widget_InspectorProperty* prop);
	void									on_object_property_changed(Widget_InspectorProperty* prop);
private:
	Widget_Inspector*						m_pInspector;
	ld3d::GameObject*						m_pObj;
};

#endif // FORM_INSPECTOR_H
