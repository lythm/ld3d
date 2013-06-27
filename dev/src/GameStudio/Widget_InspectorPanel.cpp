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

	
	//setStyleSheet("background-color:rgb(56,56,56);}");

	m_indent = 20;
	m_pBar = new Widget_InspectorPanelBar(this);

	connect(m_pBar, SIGNAL(clicked()), this, SLOT(slotTitleClicked()));
	setMinimumWidth(100);
	//setMinimumHeight(WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING);
}


Widget_InspectorPanel::~Widget_InspectorPanel(void)
{
}
void Widget_InspectorPanel::resizeEvent(QResizeEvent* e)
{
	m_pBar->setGeometry(0, 0, e->size().width(), WIDGET_ROW_HEIGHT);

	int h = m_pBar->sizeHint().height();

	for(auto v : m_props)
	{
		if(v->isVisibleTo(this) == false)
		{
			continue;
		}

		QSize size = v->sizeHint();

		v->setGeometry(m_indent, h, e->size().width() - m_indent, size.height());
		h += size.height() + WIDGET_ROW_SPACING;
	}
	QWidget::resizeEvent(e);
}
void Widget_InspectorPanel::AddProperty(Widget_InspectorProperty* pProp)
{
	pProp->setParent(this);
	pProp->setVisible(true);
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

QSize Widget_InspectorPanel::sizeHint() const
{
	int w = 0;
	int h = 0;

	w = w < m_pBar->sizeHint().width() ? m_pBar->sizeHint().width() : w;
	h += m_pBar->sizeHint().height() + WIDGET_ROW_SPACING;

	for(auto v : m_props)
	{
		if(v->isVisibleTo(this) == false)
		{
			continue;
		}
		w = w < v->sizeHint().width() ? v->sizeHint().width() : w;
		h += v->sizeHint().height() + WIDGET_ROW_SPACING;

	}

	return QSize(w, h);
}
void Widget_InspectorPanel::slotTitleClicked()
{
	for(auto v : m_props)
	{
		bool visible = v->isVisible();
		v->setVisible(!visible);
	}
	QWidget* pWidget = this;
	while(pWidget)
	{
		pWidget->updateGeometry();
		pWidget = pWidget->parentWidget();
	}
}
