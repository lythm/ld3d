#include "stdafx.h"
#include "Widget_InspectorPanel.h"
#include "Widget_InspectorPanelBar.h"
#include "widget_inspectorpropertystring.h"
#include "widget_inspectorpropertyint.h"
#include "widget_inspectorpropertydouble.h"
#include "Widget_InspectorPropertyBool.h"
#include "Widget_InspectorPropertyColor.h"
#include "Widget_InspectorPropertyTransform.h"


Widget_InspectorPanel::Widget_InspectorPanel(QWidget* parent, const QString& name)
	:Widget_InspectorProperty(parent)
{
	m_indent = 10;
	m_pBar = new Widget_InspectorPanelBar(this);

	setMinimumWidth(100);
	setMinimumHeight(WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING);
}


Widget_InspectorPanel::~Widget_InspectorPanel(void)
{
}
void Widget_InspectorPanel::resizeEvent(QResizeEvent* e)
{
	m_pBar->setGeometry(0, 0, e->size().width(), WIDGET_ROW_HEIGHT);

	int h = m_pBar->minimumHeight();

	for(auto v : m_props)
	{
		v->setGeometry(m_indent, h, e->size().width() - m_indent, v->minimumHeight());
		h += v->minimumHeight() + WIDGET_ROW_SPACING;
	}
	QWidget::resizeEvent(e);
}
void Widget_InspectorPanel::AddProperty(Widget_InspectorProperty* pProp)
{
	int h = minimumHeight();

	h += pProp->minimumHeight() + WIDGET_ROW_SPACING;

	setMinimumHeight(h);

	pProp->setParent(this);
	m_props.push_back(pProp);
}
Widget_InspectorProperty* Widget_InspectorPanel::AddStringProperty(const QString& name, const QString& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyString(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_InspectorPanel::AddIntProperty(const QString& name, int initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyInt(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_InspectorPanel::AddDoubleProperty(const QString& name, double initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyDouble(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_InspectorPanel::AddBoolProperty(const QString& name, bool initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyBool(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_InspectorPanel::AddColorProperty(const QString& name, const QColor& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyColor(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_InspectorPanel::AddTransformProperty(const math::Matrix44& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyTransform(this, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorPanel* Widget_InspectorPanel::AddPanel()
{
	Widget_InspectorPanel* pPanel = new Widget_InspectorPanel(this);

	AddProperty(pPanel);
	return pPanel;
}

