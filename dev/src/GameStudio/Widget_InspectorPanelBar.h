#pragma once


class Widget_InspectorPanelBar : public QWidget
{
	Q_OBJECT
public:
	Widget_InspectorPanelBar(QWidget* parent);
	virtual ~Widget_InspectorPanelBar(void);

	void											resizeEvent(QResizeEvent* e);
private:
	QLabel*											m_pTitle;
};

