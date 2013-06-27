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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Inspector
{
public:
    QGridLayout *inspector_layout;

    void setupUi(QWidget *Form_Inspector)
    {
        if (Form_Inspector->objectName().isEmpty())
            Form_Inspector->setObjectName(QStringLiteral("Form_Inspector"));
        Form_Inspector->resize(317, 724);
        Form_Inspector->setStyleSheet(QLatin1String("\n"
"QLineEdit\n"
"{\n"
"	border: 1px solid rgb(70, 70, 70);\n"
"	background-color: rgb(65, 65, 65);\n"
"}\n"
"\n"
"Widget_Inspector\n"
"{\n"
"	background-color: rgb(255, 89, 89);\n"
"}\n"
"Widget_InspectorPanel\n"
"{\n"
"	background-color: rgb(255, 89, 89);\n"
"}\n"
"Widget_InspectorPanelBar\n"
"{\n"
"	background-color: rgb(255, 89, 89);\n"
"}\n"
"Widget_InspectorProperty\n"
"{\n"
"	background-color: rgb(255, 89, 89);\n"
"}\n"
"QPushButton\n"
"{\n"
"	background-color: rgb(255, 89, 89);\n"
"}\n"
""));
        inspector_layout = new QGridLayout(Form_Inspector);
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
