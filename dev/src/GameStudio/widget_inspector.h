#ifndef WIDGET_INSPECTOR_H
#define WIDGET_INSPECTOR_H

#include <QWidget>


class Widget_InspectorProperty;
class Widget_InspectorPanel;

class Widget_Inspector : public QWidget
{
	Q_OBJECT

public:

	Widget_Inspector(QWidget *parent);
	virtual ~Widget_Inspector();


	class InspectorLayout : public QLayout
	{
	public:
		InspectorLayout(QWidget *parent): QLayout(parent) 
		{
			setSpacing(1);
		}
		virtual ~InspectorLayout();

		void addItem(QLayoutItem *item);
		QSize sizeHint() const;
		QSize minimumSize() const;
		int count() const;
		QLayoutItem *itemAt(int) const;
		QLayoutItem *takeAt(int);
		void setGeometry(const QRect &rect);

	
	private:
		QList<QLayoutItem*>						list;

	};
public:

	void										RemoveAll();

	Widget_InspectorPanel*						AddPanel(const QString& name);
	
	Widget_InspectorProperty*					AddPathProperty(const QString& name, const boost::filesystem::path& initValue);
	Widget_InspectorProperty*					AddStringProperty(const QString& name, const QString& initValue);
	Widget_InspectorProperty*					AddIntProperty(const QString& name, int initValue);
	Widget_InspectorProperty*					AddDoubleProperty(const QString& name, double initValue);
	Widget_InspectorProperty*					AddBoolProperty(const QString& name, bool initValue);
	Widget_InspectorProperty*					AddColorProperty(const QString& name, const QColor& initValue);
	Widget_InspectorProperty*					AddTransformProperty(const math::Matrix44& initValue);

	void										AddProperty(Widget_InspectorProperty* pProp);

	void										paintEvent(QPaintEvent *);


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

private:
	void										resizeEvent(QResizeEvent* e);
private:
	std::vector<Widget_InspectorProperty*>		m_props;

	InspectorLayout*							m_pLayout;

};

#endif // WIDGET_INSPECTOR_H
