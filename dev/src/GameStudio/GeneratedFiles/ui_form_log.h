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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Log
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabInfo;
    QGridLayout *gridLayout_2;
    QTextBrowser *textInfo;
    QWidget *tabBuild;
    QGridLayout *gridLayout_3;
    QTextBrowser *textBuild;

    void setupUi(QWidget *Form_Log)
    {
        if (Form_Log->objectName().isEmpty())
            Form_Log->setObjectName(QStringLiteral("Form_Log"));
        Form_Log->resize(766, 224);
        gridLayout = new QGridLayout(Form_Log);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(Form_Log);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabInfo = new QWidget();
        tabInfo->setObjectName(QStringLiteral("tabInfo"));
        gridLayout_2 = new QGridLayout(tabInfo);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textInfo = new QTextBrowser(tabInfo);
        textInfo->setObjectName(QStringLiteral("textInfo"));

        gridLayout_2->addWidget(textInfo, 0, 0, 1, 1);

        tabWidget->addTab(tabInfo, QString());
        tabBuild = new QWidget();
        tabBuild->setObjectName(QStringLiteral("tabBuild"));
        gridLayout_3 = new QGridLayout(tabBuild);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textBuild = new QTextBrowser(tabBuild);
        textBuild->setObjectName(QStringLiteral("textBuild"));

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
        textInfo->setHtml(QApplication::translate("Form_Log", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">infomation</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabInfo), QApplication::translate("Form_Log", "Infomation", 0));
        textBuild->setHtml(QApplication::translate("Form_Log", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">build</p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabBuild), QApplication::translate("Form_Log", "Build", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Log: public Ui_Form_Log {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_LOG_H
