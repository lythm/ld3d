/********************************************************************************
** Form generated from reading UI file 'form_scene.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_SCENE_H
#define UI_FORM_SCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMdiSubWindow>

QT_BEGIN_NAMESPACE

class Ui_Form_Scene
{
public:

    void setupUi(QMdiSubWindow *Form_Scene)
    {
        if (Form_Scene->objectName().isEmpty())
            Form_Scene->setObjectName(QStringLiteral("Form_Scene"));
        Form_Scene->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form_Scene->sizePolicy().hasHeightForWidth());
        Form_Scene->setSizePolicy(sizePolicy);
        Form_Scene->setStyleSheet(QLatin1String("background-color: rgb(56, 56, 56);\n"
"background-color: rgb(38, 38, 38);\n"
"border-color: rgb(137, 101, 255);"));

        retranslateUi(Form_Scene);

        QMetaObject::connectSlotsByName(Form_Scene);
    } // setupUi

    void retranslateUi(QMdiSubWindow *Form_Scene)
    {
        Form_Scene->setWindowTitle(QApplication::translate("Form_Scene", "Form_Scene", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Scene: public Ui_Form_Scene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_SCENE_H