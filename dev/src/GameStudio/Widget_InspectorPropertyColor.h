#pragma once

#include "widget_inspectorpropertysimple.h"
#include "Widget_ColorButton.h"

class Widget_InspectorPropertyColor : public Widget_InspectorPropertySimple
{
public:
	Q_OBJECT
public:
	Widget_InspectorPropertyColor(QWidget *parent, const QString& name = "name", const QColor& value = QColor(255, 255, 255));
	virtual ~Widget_InspectorPropertyColor(void);


	QColor								GetValue();
	void								SetValue(const QColor& value);
	

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
	void								on_value_changed(const QColor&);
private:
	Widget_ColorButton					m_value;

};

