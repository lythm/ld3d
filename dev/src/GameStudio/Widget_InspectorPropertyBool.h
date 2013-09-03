#pragma once
#include "widget_inspectorpropertysimple.h"


class Widget_InspectorPropertyBool : public Widget_InspectorPropertySimple
{
public:
	Q_OBJECT
public:
	Widget_InspectorPropertyBool(QWidget *parent, const QString& name = "name", bool value = false);
	virtual ~Widget_InspectorPropertyBool(void);


	bool								GetValue();
	void								SetValue(bool value);


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
	void								on_value_changed(int);

private:
	QCheckBox							m_value;

};

