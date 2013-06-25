#include "stdafx.h"
#include "widget_inspectorpropertysimple.h"

Widget_InspectorPropertySimple::Widget_InspectorPropertySimple(QWidget *parent, const QString& name, void* userData)
	: Widget_InspectorProperty(parent, userData)
{

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	setMinimumHeight(19);
	
	m_pNameWidget = new QLabel(this);
	m_pNameWidget->setAttribute(Qt::WA_DeleteOnClose);
	m_pValueWidget = nullptr;

	SetName(name);

	//setMinimumWidth(m_pNameWidget->minimumWidth() + 20);
	//setMinimumWidth(300);
}

Widget_InspectorPropertySimple::~Widget_InspectorPropertySimple()
{

}
void Widget_InspectorPropertySimple::resizeEvent(QResizeEvent* e)
{
	QSize s = e->size();

	int w1 = s.width() / 3;

	m_pNameWidget->setGeometry(0, 0, w1 - 1, 19);

	if(m_pValueWidget)
	{
		m_pValueWidget->setGeometry(w1 , 0, s.width() - w1 - 1 , 19);
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
