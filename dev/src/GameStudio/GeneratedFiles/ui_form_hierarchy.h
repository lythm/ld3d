/********************************************************************************
** Form generated from reading UI file 'form_hierarchy.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_HIERARCHY_H
#define UI_FORM_HIERARCHY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Hierarchy
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;

    void setupUi(QWidget *Form_Hierarchy)
    {
        if (Form_Hierarchy->objectName().isEmpty())
            Form_Hierarchy->setObjectName(QStringLiteral("Form_Hierarchy"));
        Form_Hierarchy->resize(304, 608);
        Form_Hierarchy->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));
        gridLayout = new QGridLayout(Form_Hierarchy);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeView = new QTreeView(Form_Hierarchy);
        treeView->setObjectName(QStringLiteral("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);


        retranslateUi(Form_Hierarchy);

        QMetaObject::connectSlotsByName(Form_Hierarchy);
    } // setupUi

    void retranslateUi(QWidget *Form_Hierarchy)
    {
        Form_Hierarchy->setWindowTitle(QApplication::translate("Form_Hierarchy", "Scene Hierarchy", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Hierarchy: public Ui_Form_Hierarchy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_HIERARCHY_H
