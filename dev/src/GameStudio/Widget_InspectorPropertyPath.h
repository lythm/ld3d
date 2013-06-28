#pragma once

#include "widget_inspectorproperty.h"

class Widget_InspectorPropertyPath : public Widget_InspectorProperty
{
	Q_OBJECT
public:
	Widget_InspectorPropertyPath(QWidget *parent, const QString& name, const boost::filesystem::path& value="");
	~Widget_InspectorPropertyPath(void);


	virtual void								resizeEvent(QResizeEvent* e);
	void										SetName(const QString& name);
	QString										GetName();

	boost::filesystem::path						GetValue();
	void										SetValue(const boost::filesystem::path& value);

	QSize										sizeHint() const;

public slots:
	void										slotPickPath();
	void										on_value_changed();
private:
	QLabel*										m_pName;
	QPushButton*								m_pPickButton;
	QLineEdit*									m_pValue;
};

