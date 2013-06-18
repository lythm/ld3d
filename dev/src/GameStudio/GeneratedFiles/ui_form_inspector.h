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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Inspector
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QComboBox *comboBox;

    void setupUi(QWidget *Form_Inspector)
    {
        if (Form_Inspector->objectName().isEmpty())
            Form_Inspector->setObjectName(QStringLiteral("Form_Inspector"));
        Form_Inspector->resize(437, 432);
        Form_Inspector->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));
        formLayout = new QFormLayout(Form_Inspector);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(Form_Inspector);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_3 = new QLabel(Form_Inspector);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        lineEdit = new QLineEdit(Form_Inspector);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        comboBox = new QComboBox(Form_Inspector);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox);


        retranslateUi(Form_Inspector);

        QMetaObject::connectSlotsByName(Form_Inspector);
    } // setupUi

    void retranslateUi(QWidget *Form_Inspector)
    {
        Form_Inspector->setWindowTitle(QApplication::translate("Form_Inspector", "Form_Inspector", 0));
        label->setText(QApplication::translate("Form_Inspector", "TextLabel", 0));
        label_3->setText(QApplication::translate("Form_Inspector", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Inspector: public Ui_Form_Inspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_INSPECTOR_H
