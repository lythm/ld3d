#pragma once
#include "widget_inspectorproperty.h"

class Widget_InspectorPanelBar;
class Widget_InspectorPanel: public Widget_InspectorProperty
{
	Q_OBJECT
public:
	Widget_InspectorPanel(QWidget* parent, const QString& name = "Panel");
	virtual ~Widget_InspectorPanel(void);

	void										resizeEvent(QResizeEvent* e);


	Widget_InspectorPanel*						AddPanel();
	Widget_InspectorProperty*					AddStringProperty(const QString& name, const QString& initValue);
	Widget_InspectorProperty*					AddIntProperty(const QString& name, int initValue);
	Widget_InspectorProperty*					AddDoubleProperty(const QString& name, double initValue);
	Widget_InspectorProperty*					AddBoolProperty(const QString& name, bool initValue);
	Widget_InspectorProperty*					AddColorProperty(const QString& name, const QColor& initValue);
	Widget_InspectorProperty*					AddTransformProperty(const math::Matrix44& initValue);

	void										AddProperty(Widget_InspectorProperty* pProp);

	QSize										sizeHint() const;

	void										paintEvent(QPaintEvent *);
public
Q_SLOTS:
	void										slotTitleClicked();
private:
	Widget_InspectorPanelBar*					m_pBar;
	std::vector<Widget_InspectorProperty*>		m_props;

	int											m_indent;
};

