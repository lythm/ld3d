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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Form_ProjectWizard
{
public:
    QGridLayout *gridLayout;
    QPushButton *browseBtn;
    QPushButton *createBtn;
    QLineEdit *nameEdit;
    QLineEdit *locEdit;
    QListWidget *listWidget;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;

    void setupUi(QDialog *Form_ProjectWizard)
    {
        if (Form_ProjectWizard->objectName().isEmpty())
            Form_ProjectWizard->setObjectName(QStringLiteral("Form_ProjectWizard"));
        Form_ProjectWizard->setWindowModality(Qt::WindowModal);
        Form_ProjectWizard->resize(460, 590);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form_ProjectWizard->sizePolicy().hasHeightForWidth());
        Form_ProjectWizard->setSizePolicy(sizePolicy);
        Form_ProjectWizard->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"font: 9pt \"Arial\";\n"
"background-color: rgb(255, 255, 255);"));
        Form_ProjectWizard->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(Form_ProjectWizard);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        browseBtn = new QPushButton(Form_ProjectWizard);
        browseBtn->setObjectName(QStringLiteral("browseBtn"));

        gridLayout->addWidget(browseBtn, 3, 1, 1, 1);

        createBtn = new QPushButton(Form_ProjectWizard);
        createBtn->setObjectName(QStringLiteral("createBtn"));

        gridLayout->addWidget(createBtn, 6, 1, 1, 1);

        nameEdit = new QLineEdit(Form_ProjectWizard);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        gridLayout->addWidget(nameEdit, 1, 0, 1, 1);

        locEdit = new QLineEdit(Form_ProjectWizard);
        locEdit->setObjectName(QStringLiteral("locEdit"));
        locEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);

        gridLayout->addWidget(locEdit, 3, 0, 1, 1);

        listWidget = new QListWidget(Form_ProjectWizard);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setCheckState(Qt::Unchecked);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setCheckState(Qt::Unchecked);
        __qlistwidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 5, 0, 1, 2);

        label_2 = new QLabel(Form_ProjectWizard);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        label = new QLabel(Form_ProjectWizard);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_3 = new QLabel(Form_ProjectWizard);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 5);

        retranslateUi(Form_ProjectWizard);

        QMetaObject::connectSlotsByName(Form_ProjectWizard);
    } // setupUi

    void retranslateUi(QDialog *Form_ProjectWizard)
    {
        Form_ProjectWizard->setWindowTitle(QApplication::translate("Form_ProjectWizard", "Project Wizzard", 0));
        browseBtn->setText(QApplication::translate("Form_ProjectWizard", "Browse...", 0));
        createBtn->setText(QApplication::translate("Form_ProjectWizard", "Create", 0));
        locEdit->setPlaceholderText(QString());

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Form_ProjectWizard", "Core", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Form_ProjectWizard", "Voxel", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_2->setText(QApplication::translate("Form_ProjectWizard", "Packges to import:", 0));
        label->setText(QApplication::translate("Form_ProjectWizard", "Project Location:", 0));
        label_3->setText(QApplication::translate("Form_ProjectWizard", "Project Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_ProjectWizard: public Ui_Form_ProjectWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PROJECTWIZARD_H
