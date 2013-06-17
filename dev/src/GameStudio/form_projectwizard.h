#ifndef FORM_PROJECTWIZARD_H
#define FORM_PROJECTWIZARD_H

#include <QDialog>
#include "ui_form_projectwizard.h"

class Form_ProjectWizard : public QDialog, public Ui::Form_ProjectWizard
{
	Q_OBJECT

public:
	Form_ProjectWizard(QWidget *parent = 0);
	~Form_ProjectWizard();
};

#endif // FORM_PROJECTWIZARD_H
