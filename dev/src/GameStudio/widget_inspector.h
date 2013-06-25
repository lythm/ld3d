#ifndef WIDGET_INSPECTOR_H
#define WIDGET_INSPECTOR_H

#include <QWidget>
class Widget_InspectorProperty;


class Widget_InspectorProperty;

class Widget_Inspector : public QWidget
{
	Q_OBJECT

public:

	Widget_Inspector(QWidget *parent = 0);
	virtual ~Widget_Inspector();


	class InspectorLayout : public QLayout
	{
	public:
		InspectorLayout(QWidget *parent): QLayout(parent) {setSpacing(1);}
		virtual ~InspectorLayout();

		void addItem(QLayoutItem *item);
		QSize sizeHint() const;
		QSize minimumSize() const;
		int count() const;
		QLayoutItem *itemAt(int) const;
		QLayoutItem *takeAt(int);
		void setGeometry(const QRect &rect);

	private:
		QList<QLayoutItem*> list;
	};
public:
	
	Widget_InspectorProperty*					AddStringProperty(const QString& name, const QString& initValue);
	void										AddProperty(Widget_InspectorProperty* pProp);
private:
	void										resizeEvent(QResizeEvent* e);
private:
	Widget_InspectorProperty*					m_pProperty;

	InspectorLayout*							m_pLayout;
};

#endif // WIDGET_INSPECTOR_H
