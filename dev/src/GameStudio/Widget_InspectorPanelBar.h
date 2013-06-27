#pragma once


class Widget_InspectorPanelBar : public QWidget
{
	Q_OBJECT
public:
	Widget_InspectorPanelBar(QWidget* parent, const QString& name);
	virtual ~Widget_InspectorPanelBar(void);

	void											resizeEvent(QResizeEvent* e);
	QSize											sizeHint() const;

public:
Q_SIGNALS:
	void											clicked();

private:
	QPushButton*									m_pTitle;
};

