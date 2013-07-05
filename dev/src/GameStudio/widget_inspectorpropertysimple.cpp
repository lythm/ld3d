#include "stdafx.h"
#include "widget_inspectorpropertysimple.h"

Widget_InspectorPropertySimple::Widget_InspectorPropertySimple(QWidget *parent, const QString& name, void* userData)
	: Widget_InspectorProperty(parent, userData)
{

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
		
	m_pNameWidget = new QLabel(this);
	m_pNameWidget->setAttribute(Qt::WA_DeleteOnClose);
	m_pValueWidget = nullptr;

	SetName(name);

	setMinimumWidth(100);
	setMinimumHeight(WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING);

}

Widget_InspectorPropertySimple::~Widget_InspectorPropertySimple()
{

}
void Widget_InspectorPropertySimple::resizeEvent(QResizeEvent* e)
{
	QSize s = e->size();

	int w1 = 100;

	m_pNameWidget->setGeometry(0, 0, w1 - 1, WIDGET_ROW_HEIGHT);

	if(m_pValueWidget)
	{
		m_pValueWidget->setGeometry(w1 , 0, s.width() - w1 - 1 , WIDGET_ROW_HEIGHT);
	}

	Widget_InspectorProperty::resizeEvent(e);
}
void Widget_InspectorPropertySimple::SetValueWidget(QWidget* pValue)
{
	m_pValueWidget = pValue;
	//m_pValueWidget->setAttribute(Qt::WA_DeleteOnClose);
	m_pValueWidget->setParent(this);

	setMinimumWidth(m_pNameWidget->sizeHint().width() + m_pValueWidget->minimumWidth() + 1);
}
void Widget_InspectorPropertySimple::SetName(const QString& name)
{
	m_pNameWidget->setText(name);
}
QString	Widget_InspectorPropertySimple::GetName()
{
	return m_pNameWidget->text();
}
QSize Widget_InspectorPropertySimple::sizeHint() const
{
	return QSize(100, WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING);
}