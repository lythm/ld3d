#pragma once


class Widget_InspectorPanelBar : public QWidget
{
	Q_OBJECT
public:
	Widget_InspectorPanelBar(QWidget* parent, const QString& name);
	virtual ~Widget_InspectorPanelBar(void);

	void											resizeEvent(QResizeEvent* e);
	QSize											sizeHint() const;

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

public:
Q_SIGNALS:
	void											clicked();

private:
	QPushButton*									m_pTitle;
};

