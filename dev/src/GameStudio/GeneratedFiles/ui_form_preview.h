/********************************************************************************
** Form generated from reading UI file 'form_preview.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PREVIEW_H
#define UI_FORM_PREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMdiSubWindow>

QT_BEGIN_NAMESPACE

class Ui_Form_Preview
{
public:

    void setupUi(QMdiSubWindow *Form_Preview)
    {
        if (Form_Preview->objectName().isEmpty())
            Form_Preview->setObjectName(QStringLiteral("Form_Preview"));
        Form_Preview->resize(400, 300);
        Form_Preview->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));

        retranslateUi(Form_Preview);

        QMetaObject::connectSlotsByName(Form_Preview);
    } // setupUi

    void retranslateUi(QMdiSubWindow *Form_Preview)
    {
        Form_Preview->setWindowTitle(QApplication::translate("Form_Preview", "Form_Preview", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Preview: public Ui_Form_Preview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PREVIEW_H
