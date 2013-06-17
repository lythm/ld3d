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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Inspector
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *Form_Inspector)
    {
        if (Form_Inspector->objectName().isEmpty())
            Form_Inspector->setObjectName(QStringLiteral("Form_Inspector"));
        Form_Inspector->resize(247, 590);
        Form_Inspector->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));
        gridLayout = new QGridLayout(Form_Inspector);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(Form_Inspector);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);


        retranslateUi(Form_Inspector);

        QMetaObject::connectSlotsByName(Form_Inspector);
    } // setupUi

    void retranslateUi(QWidget *Form_Inspector)
    {
        Form_Inspector->setWindowTitle(QApplication::translate("Form_Inspector", "Form_Inspector", 0));
        pushButton->setText(QApplication::translate("Form_Inspector", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Inspector: public Ui_Form_Inspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_INSPECTOR_H
