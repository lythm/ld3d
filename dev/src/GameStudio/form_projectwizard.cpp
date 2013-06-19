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
	QString name = nameEdit->text();
	QString loc = locEdit->text();

	boost::filesystem::path root = boost::filesystem::path(loc.toStdWString())
							/ boost::filesystem::path(name.toStdWString());
	if(boost::filesystem::exists(root))
	{
		QMessageBox::critical(this, "Failed", "Project exists.");
		return;
	}
	boost::filesystem::create_directory(root);

	m_filePath = root / boost::filesystem::path((name + ".gp").toStdWString());

	done(Accepted);
}

boost::filesystem::path Form_ProjectWizard::ProjectFilePath()
{
	return m_filePath;
}