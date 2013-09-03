#ifndef WIDGET_INSPECTORPROPERTY_H
#define WIDGET_INSPECTORPROPERTY_H

#include <QWidget>

class Widget_InspectorProperty : public QWidget
{
	Q_OBJECT

public:
	Widget_InspectorProperty(QWidget *parent, void* userData = nullptr);
	~Widget_InspectorProperty();

	enum
	{
		WIDGET_ROW_HEIGHT			= 16,
		WIDGET_ROW_SPACING			= 1,
	};

	void															SetUserData(void* data);
	void*															GetUserData();

	virtual void													Release();

	std::function<void(Widget_InspectorProperty*)>					on_property_changed;


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
	void															resizeEvent(QResizeEvent* e);
		
private:
	
	void*															m_pUserData;
};


#endif // WIDGET_INSPECTORPROPERTY_H
