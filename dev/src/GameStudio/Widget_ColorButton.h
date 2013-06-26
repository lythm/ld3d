#pragma once


class Widget_ColorButton : public QAbstractButton
{
	Q_OBJECT
public:
	Widget_ColorButton(QWidget* parent, const QColor& initValue);
	virtual ~Widget_ColorButton(void);


	void									setColor(const QColor& clr);
	const QColor&							color();


public:
Q_SIGNALS:
	void									colorChanged(const QColor& clr);
private:
	void									initStyleOption(QStyleOptionButton *option);
	void									paintEvent(QPaintEvent *);

private Q_SLOTS:
	void									slotPickColor();

private:
	QColor									m_color;
};

