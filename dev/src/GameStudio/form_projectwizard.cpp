#include "stdafx.h"
#include "form_projectwizard.h"

Form_ProjectWizard::Form_ProjectWizard(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

Form_ProjectWizard::~Form_ProjectWizard()
{

}
void Form_ProjectWizard::on_browseBtn_clicked()
{
	QFileDialog dlg(this);

	dlg.setFileMode(QFileDialog::Directory);
	dlg.setOption(QFileDialog::ShowDirsOnly, true);

	if(QDialog::Rejected == dlg.exec())
	{
		return;
	}

	QString s = dlg.selectedFiles().first();
	locEdit->setText(s);

}
void Form_ProjectWizard::on_createBtn_clicked()
{
	if(nameEdit->text().isEmpty())
	{
		QMessageBox::critical(this, "Failed", "Project name can not be empty.");
		return;
	}

	if(locEdit->text().isEmpty())
	{
		QMessageBox::critical(this, "Failed", "Project location is not valid.");
		return;
	}


	done(Accepted);
}
