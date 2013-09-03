#pragma once
#include "widget_inspectorpropertysimple.h"


class Widget_InspectorPropertyDouble : public Widget_InspectorPropertySimple
{
public:
	Q_OBJECT
public:
	Widget_InspectorPropertyDouble(QWidget *parent, const QString& name = "name", double value = 0);
	virtual ~Widget_InspectorPropertyDouble(void);


	double								GetValue();
	void								SetValue(double value);


	static void* operator new(size_t size)
	{
		return g_Allocator.Alloc(size);
		//return ::operator new(size);
	}

	static void operator delete(void* pointee)
	{
		//::operator delete(pointee);
		g_Allocator.Free(pointee);
	}

public slots:
	void								on_value_changed();
private:
	QLineEdit							m_value;

	QDoubleValidator					m_validator;
};

