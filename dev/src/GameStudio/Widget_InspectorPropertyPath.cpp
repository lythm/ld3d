#include "stdafx.h"
#include "Widget_InspectorPropertyPath.h"


Widget_InspectorPropertyPath::Widget_InspectorPropertyPath(QWidget *parent, const QString& name, const boost::filesystem::path& value)
	: Widget_InspectorProperty(parent)
{
	m_pPickButton = new QPushButton(this);
	m_pPickButton->setText("...");

	m_pValue = new QLineEdit(this);
	SetValue(value);

	m_pName = new QLabel(this);
	m_pName->setText(name);

	connect(m_pValue, SIGNAL(editingFinished()), this, SLOT(on_value_changed()));

	connect(m_pPickButton, SIGNAL(clicked()), this, SLOT(slotPickPath()));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}


Widget_InspectorPropertyPath::~Widget_InspectorPropertyPath(void)
{
}
void Widget_InspectorPropertyPath::resizeEvent(QResizeEvent* e)
{
	QSize s = e->size();

	int w1 = 100;
	int w2 = 30;

	m_pName->setGeometry(0, 0, w1 - 1, WIDGET_ROW_HEIGHT);

	m_pValue->setGeometry(w1 , 0, s.width() - w2 - w1 - 2 , WIDGET_ROW_HEIGHT);

	m_pPickButton->setGeometry(s.width() - w2, 0, w2, WIDGET_ROW_HEIGHT);
	
	Widget_InspectorProperty::resizeEvent(e);
}

void Widget_InspectorPropertyPath::SetName(const QString& name)
{
	m_pName->setText(name);
}
QString	Widget_InspectorPropertyPath::GetName()
{
	return m_pName->text();
}
QSize Widget_InspectorPropertyPath::sizeHint() const
{
	return QSize(100, WIDGET_ROW_HEIGHT + WIDGET_ROW_SPACING);
}
void Widget_InspectorPropertyPath::slotPickPath()
{
	QString str = QFileDialog::getOpenFileName(this);
	if(str == "")
	{
		return;
	}

	SetValue(str.toStdWString());

	on_value_changed();

}
boost::filesystem::path	Widget_InspectorPropertyPath::GetValue()
{
	return boost::filesystem::path(m_pValue->text().toStdWString());
}
void Widget_InspectorPropertyPath::SetValue(const boost::filesystem::path& value)
{
	QString str = QString::fromStdWString(value.wstring());
	m_pValue->setText(str);
}
void Widget_InspectorPropertyPath::on_value_changed()
{
	on_property_changed ? on_property_changed(this) : 0;
}
