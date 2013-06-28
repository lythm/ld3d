#include "stdafx.h"
#include "Widget_InspectorPanel.h"
#include "Widget_InspectorPanelBar.h"
#include "widget_inspectorpropertystring.h"
#include "widget_inspectorpropertyint.h"
#include "widget_inspectorpropertydouble.h"
#include "Widget_InspectorPropertyBool.h"
#include "Widget_InspectorPropertyColor.h"
#include "Widget_InspectorPropertyTransform.h"
#include "Widget_InspectorPropertyPath.h"


Widget_InspectorPanel::Widget_InspectorPanel(QWidget* parent, const QString& name)
	:Widget_InspectorProperty(parent)
{
	m_indent = 3;
	m_pBar = new Widget_InspectorPanelBar(this, name);

	connect(m_pBar, SIGNAL(clicked()), this, SLOT(slotTitleClicked()));
	setMinimumWidth(100);
	setAutoFillBackground(true);
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
	QWidget* pWidget = this;
	while(pWidget)
	{
		pWidget->updateGeometry();
		pWidget = pWidget->parentWidget();
	}

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
void Widget_InspectorPanel::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


	p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(QBrush(QColor(89, 89, 89)), 1));

	QRect rc = rect();
    p.drawLine(QLine(0, rc.height(), rc.width(), rc.height()));
}

Widget_InspectorProperty* Widget_InspectorPanel::AddPathProperty(const QString& name, const boost::filesystem::path& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyPath(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
void Widget_InspectorPanel::Release()
{
	for(auto v : m_props)
	{
		v->Release();
	}
	m_props.clear();

	Widget_InspectorProperty::Release();
}
