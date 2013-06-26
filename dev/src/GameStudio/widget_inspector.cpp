#include "stdafx.h"
#include "widget_inspector.h"
#include "widget_inspectorpropertystring.h"
#include "widget_inspectorpropertyint.h"
#include "widget_inspectorpropertydouble.h"
#include "Widget_InspectorPropertyBool.h"
#include "Widget_InspectorPropertyColor.h"
#include "Widget_InspectorPropertyTransform.h"

#include "AppContext.h"

Widget_Inspector::InspectorLayout::~InspectorLayout()
{
	QLayoutItem *item;
	while ((item = takeAt(0)))
		delete item;
}
int Widget_Inspector::InspectorLayout::count() const
{
	// QList::size() returns the number of QLayoutItems in the list
	return list.size();
}

QLayoutItem *Widget_Inspector::InspectorLayout::itemAt(int idx) const
{
	// QList::value() performs index checking, and returns 0 if we are
	// outside the valid range
	return list.value(idx);
}

QLayoutItem *Widget_Inspector::InspectorLayout::takeAt(int idx)
{
	// QList::take does not do index checking
	return idx >= 0 && idx < list.size() ? list.takeAt(idx) : 0;
}

void Widget_Inspector::InspectorLayout::addItem(QLayoutItem *item)
{
	list.append(item);
}
void Widget_Inspector::InspectorLayout::setGeometry(const QRect &r)
{
	QLayout::setGeometry(r);

	if (list.size() == 0)
		return;

	int w = r.width();
	int h = r.height() - (list.count() - 1) * spacing();
	int i = 0;
	int y_offset = 0;
	while (i < list.size()) {
		QLayoutItem *o = list.at(i);
		
		QRect geom(r.x(), r.y() + y_offset, w, o->sizeHint().height());
		o->setGeometry(geom);
		y_offset += o->sizeHint().height() + spacing();

		++i;
	}

	//QString str("%1-%2-%3-%4");
	//AppContext::log_info(str.arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).toStdWString());
}
QSize Widget_Inspector::InspectorLayout::sizeHint() const
{
	QSize s(0,0);
	int n = list.count();
	if (n > 0)
		s = QSize(100,70); //start with a nice default size
	int i = 0;

	int w = 0;
	int h = 0;

	while (i < n) {
		QLayoutItem *o = list.at(i);

		QSize hint = o->sizeHint();

		w = w < hint.width() ? hint.width() : w;
		h += hint.height();
		++i;
	}

	s = QSize(w, h);

	return s + n * QSize(0, spacing());
}

QSize Widget_Inspector::InspectorLayout::minimumSize() const
{
	QSize s(0,0);
	int n = list.count();
	int i = 0;
	int w = 0;
	int h = 0;

	while (i < n) {
		QLayoutItem *o = list.at(i);

		QSize hint = o->minimumSize();

		w = w < hint.width() ? hint.width() : w;
		h += hint.height();
		++i;
	}

	s = QSize(w, h);
	return s + n*QSize(0, spacing());
}

/////////////////////////////////

Widget_Inspector::Widget_Inspector(QWidget *parent)
	: QWidget(parent)
{
	m_pLayout = new InspectorLayout(this);

	m_pLayout->setMargin(1);
	setLayout(m_pLayout);

}

Widget_Inspector::~Widget_Inspector()
{
}
void Widget_Inspector::resizeEvent(QResizeEvent* e)
{
	QWidget::resizeEvent(e);
}
void Widget_Inspector::AddProperty(Widget_InspectorProperty* pProp)
{
	//pProp->setAttribute(Qt::WA_DeleteOnClose);
	m_pLayout->addWidget(pProp);
}
Widget_InspectorProperty* Widget_Inspector::AddStringProperty(const QString& name, const QString& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyString(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_Inspector::AddIntProperty(const QString& name, int initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyInt(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_Inspector::AddDoubleProperty(const QString& name, double initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyDouble(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_Inspector::AddBoolProperty(const QString& name, bool initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyBool(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_Inspector::AddColorProperty(const QString& name, const QColor& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyColor(this, name, initValue);

	AddProperty(pProp);
	return pProp;
}
Widget_InspectorProperty* Widget_Inspector::AddTransformProperty(const math::Matrix44& initValue)
{
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyTransform(this, initValue);

	AddProperty(pProp);
	return pProp;
}
