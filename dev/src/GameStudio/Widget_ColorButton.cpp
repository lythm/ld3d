#include "stdafx.h"
#include "Widget_ColorButton.h"


Widget_ColorButton::Widget_ColorButton(QWidget* parent, const QColor& initValue) : QAbstractButton(parent)
{
	m_color = initValue;

	connect(this, SIGNAL(clicked()), this, SLOT(slotPickColor()));
}


Widget_ColorButton::~Widget_ColorButton(void)
{
}
void Widget_ColorButton::initStyleOption(QStyleOptionButton *option)
{
	if (!option)
		return;

	option->initFrom(this);
	option->iconSize = iconSize(); //default value

	option->state |= QStyle::State_Sunken;
	option->features = QStyleOptionButton::None;
}
void Widget_ColorButton::paintEvent(QPaintEvent *)
{
	// paint button here
	QStylePainter p(this);
	QStyleOptionButton opt;
	//initStyleOption(&opt);

	p.drawControl(QStyle::CE_PushButton, opt);

	if (!isEnabled())
		return;

	const int pixSize = 10;
	QBrush br(m_color);
	{
		QPixmap pm(2 * pixSize, 2 * pixSize);
		QPainter pmp(&pm);
		pmp.fillRect(0, 0, pixSize, pixSize, Qt::white);
		pmp.fillRect(pixSize, pixSize, pixSize, pixSize, Qt::white);
		pmp.fillRect(0, pixSize, pixSize, pixSize, Qt::black);
		pmp.fillRect(pixSize, 0, pixSize, pixSize, Qt::black);
		pmp.fillRect(0, 0, 2 * pixSize, 2 * pixSize, m_color);
		br = QBrush(pm);
	}

	const int corr = 5;
	QRect r = rect().adjusted(corr, corr, -corr, -corr);
	p.setBrushOrigin((r.width() % pixSize + pixSize) / 2 + corr, (r.height() % pixSize + pixSize) / corr);
	p.fillRect(r, br);

	const QColor frameColor1(0, 0, 0, 26);
	p.setPen(frameColor1);
	p.drawRect(r.adjusted(1, 1, -2, -2));
	const QColor frameColor2(0, 0, 0, 51);
	p.setPen(frameColor2);
	p.drawRect(r.adjusted(0, 0, -1, -1));

}
void Widget_ColorButton::setColor(const QColor& clr)
{
	m_color = clr;
}
const QColor& Widget_ColorButton::color()
{
	return m_color;
}
void Widget_ColorButton::slotPickColor()
{
	QColor value = QColorDialog::getColor(m_color, this, "Select Color", QColorDialog::ShowAlphaChannel);
	
	if(value.isValid() == false)
	{
		return;
	}

	m_color = value;
	emit colorChanged(m_color);
}
