#ifndef FORM_PREVIEW_H
#define FORM_PREVIEW_H

#include <QMdiSubWindow>
#include "ui_form_preview.h"

class Form_Preview : public QMdiSubWindow, public Ui::Form_Preview
{
	Q_OBJECT

public:
	Form_Preview(QWidget *parent = 0);
	~Form_Preview();
};

#endif // FORM_PREVIEW_H
