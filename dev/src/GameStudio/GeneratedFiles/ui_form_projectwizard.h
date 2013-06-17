/********************************************************************************
** Form generated from reading UI file 'form_projectwizard.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PROJECTWIZARD_H
#define UI_FORM_PROJECTWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Form_ProjectWizard
{
public:

    void setupUi(QDialog *Form_ProjectWizard)
    {
        if (Form_ProjectWizard->objectName().isEmpty())
            Form_ProjectWizard->setObjectName(QStringLiteral("Form_ProjectWizard"));
        Form_ProjectWizard->resize(400, 300);

        retranslateUi(Form_ProjectWizard);

        QMetaObject::connectSlotsByName(Form_ProjectWizard);
    } // setupUi

    void retranslateUi(QDialog *Form_ProjectWizard)
    {
        Form_ProjectWizard->setWindowTitle(QApplication::translate("Form_ProjectWizard", "Form_ProjectWizard", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_ProjectWizard: public Ui_Form_ProjectWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PROJECTWIZARD_H
