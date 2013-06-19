#ifndef FORM_LOG_H
#define FORM_LOG_H

#include <QWidget>
#include "ui_form_log.h"

class Form_Log : public QWidget, public Ui::Form_Log
{
	Q_OBJECT

public:
	Form_Log(QWidget *parent = 0);
	~Form_Log();


	void										logInfo(const QString& str);
	void										logBuild(const QString& str);
};

#endif // FORM_LOG_H
