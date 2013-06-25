#include "stdafx.h"
#include "widget_inspector.h"
#include "widget_inspectorpropertystring.h"
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
	while (i < list.size()) {
		QLayoutItem *o = list.at(i);
		QRect geom(r.x(), r.y() + i * (spacing() + o->sizeHint().height()), w, h);
		o->setGeometry(geom);
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

	AddStringProperty("Name", "Tom");


	for(int i = 0; i < 20; ++i)
	{

		m_pLayout->addWidget(new Widget_InspectorPropertyString(this, "Type"));
		m_pLayout->addWidget(new Widget_InspectorPropertyString(this, "Age"));
		m_pLayout->addWidget(new Widget_InspectorPropertyString(this, "Desccription"));
	}

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
	Widget_InspectorProperty* pProp = new Widget_InspectorPropertyString(this, "Name", initValue);

	AddProperty(pProp);
	return pProp;
}
