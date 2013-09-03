#ifndef WIDGET_INSPECTORPROPERTYSTRING_H
#define WIDGET_INSPECTORPROPERTYSTRING_H

#include "widget_inspectorpropertysimple.h"

class Widget_InspectorPropertyString : public Widget_InspectorPropertySimple
{
	Q_OBJECT

public:
	Widget_InspectorPropertyString(QWidget *parent, const QString& name = "name", const QString& value = "");
	~Widget_InspectorPropertyString();
	
	QString								GetValue();
	void								SetValue(const QString& value);

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
	void								slotTextChanged();
private:
	QLineEdit							m_value;
};

#endif // WIDGET_INSPECTORPROPERTYSTRING_H
