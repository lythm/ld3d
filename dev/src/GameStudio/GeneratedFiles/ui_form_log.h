/********************************************************************************
** Form generated from reading UI file 'form_log.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_LOG_H
#define UI_FORM_LOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Log
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabInfo;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *textInfo;
    QWidget *tabBuild;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *textBuild;

    void setupUi(QWidget *Form_Log)
    {
        if (Form_Log->objectName().isEmpty())
            Form_Log->setObjectName(QStringLiteral("Form_Log"));
        Form_Log->resize(766, 224);
        gridLayout = new QGridLayout(Form_Log);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        tabWidget = new QTabWidget(Form_Log);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setElideMode(Qt::ElideNone);
        tabInfo = new QWidget();
        tabInfo->setObjectName(QStringLiteral("tabInfo"));
        gridLayout_2 = new QGridLayout(tabInfo);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        textInfo = new QPlainTextEdit(tabInfo);
        textInfo->setObjectName(QStringLiteral("textInfo"));
        textInfo->setFrameShape(QFrame::NoFrame);
        textInfo->setFrameShadow(QFrame::Plain);
        textInfo->setReadOnly(true);

        gridLayout_2->addWidget(textInfo, 0, 0, 1, 1);

        tabWidget->addTab(tabInfo, QString());
        tabBuild = new QWidget();
        tabBuild->setObjectName(QStringLiteral("tabBuild"));
        gridLayout_3 = new QGridLayout(tabBuild);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(1, 1, 1, 1);
        textBuild = new QPlainTextEdit(tabBuild);
        textBuild->setObjectName(QStringLiteral("textBuild"));
        textBuild->setFrameShape(QFrame::NoFrame);
        textBuild->setFrameShadow(QFrame::Plain);
        textBuild->setReadOnly(true);

        gridLayout_3->addWidget(textBuild, 0, 0, 1, 1);

        tabWidget->addTab(tabBuild, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Form_Log);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form_Log);
    } // setupUi

    void retranslateUi(QWidget *Form_Log)
    {
        Form_Log->setWindowTitle(QApplication::translate("Form_Log", "Form_Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabInfo), QApplication::translate("Form_Log", "Infomation", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabBuild), QApplication::translate("Form_Log", "Build", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Log: public Ui_Form_Log {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_LOG_H
