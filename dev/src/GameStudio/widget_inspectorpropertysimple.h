#ifndef WIDGET_INSPECTORPROPERTYSIMPLE_H
#define WIDGET_INSPECTORPROPERTYSIMPLE_H

#include "widget_inspectorproperty.h"


class Widget_InspectorPropertySimple : public Widget_InspectorProperty
{
	Q_OBJECT

public:
	Widget_InspectorPropertySimple(QWidget *parent, const QString& name = "name", void* userData = nullptr);
	~Widget_InspectorPropertySimple();


	virtual void								resizeEvent(QResizeEvent* e);
	void										SetName(const QString& name);
	QString										GetName();

	QSize										sizeHint() const;

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

protected:
	void										SetValueWidget(QWidget* pValue);

private:
	QLabel										m_nameWidget;
	QWidget*									m_pValueWidget;
};

#endif // WIDGET_INSPECTORPROPERTYSIMPLE_H
