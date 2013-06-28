/********************************************************************************
** Form generated from reading UI file 'form_inspector.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_INSPECTOR_H
#define UI_FORM_INSPECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Inspector
{
public:
    QVBoxLayout *inspector_layout;

    void setupUi(QWidget *Form_Inspector)
    {
        if (Form_Inspector->objectName().isEmpty())
            Form_Inspector->setObjectName(QStringLiteral("Form_Inspector"));
        Form_Inspector->resize(325, 740);
        Form_Inspector->setLayoutDirection(Qt::LeftToRight);
        Form_Inspector->setAutoFillBackground(false);
        Form_Inspector->setStyleSheet(QLatin1String("*\n"
"{\n"
"	\n"
"	\n"
"	font: 9pt \"Courier\";\n"
"	background-color: rgb(56, 56, 56);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"QLineEdit\n"
"{\n"
"	border-top-width:2px;\n"
"	border-top-style:solid;\n"
"	border-top-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(35, 35, 35, 255), stop:1 rgba(58, 58, 58, 255));\n"
"\n"
"	border-left-width:2px;\n"
"	border-left-style:solid;\n"
"	border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(47, 47, 47, 255), stop:1 rgba(60, 60, 60, 255));\n"
"\n"
"	border-right-width:2px;\n"
"	border-right-style:solid;\n"
"	border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(60, 60, 60, 255), stop:1 rgba(47, 47, 47, 255));\n"
"\n"
"\n"
"	border-bottom-width:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(70, 70, 70, 255), stop:1 rgba(50, 50, 50, 255));\n"
"\n"
"	background-color: rgb(65, 65, 65);\n"
"}\n"
"\n"
""));
        inspector_layout = new QVBoxLayout(Form_Inspector);
        inspector_layout->setSpacing(1);
        inspector_layout->setContentsMargins(11, 11, 11, 11);
        inspector_layout->setObjectName(QStringLiteral("inspector_layout"));
        inspector_layout->setContentsMargins(1, 1, 1, 1);

        retranslateUi(Form_Inspector);

        QMetaObject::connectSlotsByName(Form_Inspector);
    } // setupUi

    void retranslateUi(QWidget *Form_Inspector)
    {
        Form_Inspector->setWindowTitle(QApplication::translate("Form_Inspector", "Form_Inspector", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Inspector: public Ui_Form_Inspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_INSPECTOR_H
