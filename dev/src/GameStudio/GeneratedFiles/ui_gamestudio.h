/********************************************************************************
** Form generated from reading UI file 'gamestudio.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESTUDIO_H
#define UI_GAMESTUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameStudioClass
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionNew_Scene;
    QAction *actionOpen_Scene;
    QAction *actionSave_Scene;
    QAction *actionSave_Scene_As;
    QAction *actionExit;
    QAction *actionClose_Project;
    QAction *actionEmpty;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuProject;
    QMenu *menuGameObject;
    QMenu *menuComponent;
    QMenu *menuHelp;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockHierarchy;
    QWidget *dockWidgetContents;
    QDockWidget *dockLog;
    QWidget *dockWidgetContents_2;
    QDockWidget *dockInspector;
    QWidget *dockWidgetContents_3;

    void setupUi(QMainWindow *GameStudioClass)
    {
        if (GameStudioClass->objectName().isEmpty())
            GameStudioClass->setObjectName(QStringLiteral("GameStudioClass"));
        GameStudioClass->resize(1046, 809);
        QIcon icon;
        icon.addFile(QStringLiteral(":/GameStudio/i001.png"), QSize(), QIcon::Normal, QIcon::Off);
        GameStudioClass->setWindowIcon(icon);
        GameStudioClass->setStyleSheet(QLatin1String("*\n"
"\n"
"{\n"
"	color: rgb(180, 180, 180);\n"
"	background-color: rgb(41, 41, 41);\n"
"	border-color: rgb(41, 41, 41);\n"
"\n"
"}\n"
"\n"
"QMenuBar \n"
"{\n"
"	\n"
"     background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                       stop:0 rgb(80, 80, 80), stop:1 rgb(41, 41, 41));\n"
" }\n"
"\n"
" QMenuBar::item \n"
"{\n"
"     background: transparent;\n"
" }\n"
"\n"
" QMenuBar::item:selected \n"
"{ \n"
"      background-color: rgb(41, 41, 41);\n"
" }\n"
"\n"
" QMenuBar::item:pressed\n"
" {\n"
"     background-color: rgb(41, 41, 41);\n"
" }\n"
"QMenu \n"
"{\n"
"	color: rgb(180, 180, 180);\n"
"	background-color: rgb(41, 41, 41);\n"
"	border-color: rgb(41, 41, 41);\n"
"    margin: 2px; /* some spacing around the menu */\n"
"}\n"
" \n"
"QMenu::item \n"
"{\n"
"    padding: 2px 25px 2px 20px;\n"
"    border: 1px solid transparent; /* reserve space for selection border */\n"
"}\n"
" \n"
"QMenu::item:!enabled \n"
"{\n"
"	color: rgb(80, 80, 80);\n"
"    border-color:rgb(41, 41, "
                        "41);\n"
"}\n"
"QMenu::item:selected \n"
"{\n"
"    border-color:rgb(41, 41, 41);\n"
"    background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QMenu::icon:checked  { /* appearance of a 'checked' icon */\n"
"    background: gray;\n"
"    border: 1px inset gray;\n"
"    position: absolute;\n"
"    top: 1px;\n"
"    right: 1px;\n"
"    bottom: 1px;\n"
"    left: 1px;\n"
"}\n"
" \n"
"QMenu::separator  {\n"
"    height: 2px;\n"
"    background:  rgb(80, 80, 80);;\n"
"    margin-left: 10px;\n"
"    margin-right: 5px;\n"
"}\n"
" \n"
"QMenu::indicator  {\n"
"    width: 13px;\n"
"    height: 13px;\n"
"}\n"
" \n"
"/* non-exclusive indicator = check box style indicator (see QActionGroup::setExclusive) */\n"
"QMenu::indicator:non-exclusive:unchecked  {\n"
"    image: url(:/images/checkbox_unchecked.png);\n"
"}\n"
" \n"
"QMenu::indicator:non-exclusive:unchecked:selected  {\n"
"    image: url(:/images/checkbox_unchecked_hover.png);\n"
"}\n"
" \n"
"QMenu::indicator:non-exclusive:checked  {\n"
"    image: url(:/images/checkbox_check"
                        "ed.png);\n"
"}\n"
" \n"
"QMenu::indicator:non-exclusive:checked:selected  {\n"
"    image: url(:/images/checkbox_checked_hover.png);\n"
"}\n"
" \n"
"/* exclusive indicator = radio button style indicator (see QActionGroup::setExclusive) */\n"
"QMenu::indicator:exclusive:unchecked  {\n"
"    image: url(:/images/radiobutton_unchecked.png);\n"
"}\n"
" \n"
"QMenu::indicator:exclusive:unchecked:selected  {\n"
"    image: url(:/images/radiobutton_unchecked_hover.png);\n"
"}\n"
" \n"
"QMenu::indicator:exclusive:checked  {\n"
"    image: url(:/images/radiobutton_checked.png);\n"
"}\n"
" \n"
"QMenu::indicator:exclusive:checked:selected  {\n"
"    image: url(:/images/radiobutton_checked_hover.png);\n"
"}\n"
"\n"
"QToolBar\n"
"{\n"
"	color: rgb(180, 180, 180);\n"
"	background-color: rgb(41, 41, 41);\n"
"}\n"
"QToolBar:item\n"
"{\n"
"	 background-color: rgb(41, 41, 41);\n"
"}\n"
"\n"
"QTextBrowser\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}\n"
"QTreeView\n"
"{\n"
"	background-color: rgb(56, 56, 56);\n"
"}\n"
" QTr"
                        "eeView {\n"
"     show-decoration-selected: 1;\n"
" }\n"
"\n"
" QTreeView::item {\n"
"      border: 1px solid #d9d9d9;\n"
"     border-top-color: transparent;\n"
"     border-bottom-color: transparent;\n"
" }\n"
"\n"
" QTreeView::item:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);\n"
"     border: 1px solid #bfcde4;\n"
" }\n"
"\n"
" QTreeView::item:selected {\n"
"     border: 1px solid #567dbc;\n"
" }\n"
"\n"
" QTreeView::item:selected:active{\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\n"
" }\n"
"\n"
" QTreeView::item:selected:!active {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);\n"
" }\n"
""));
        GameStudioClass->setTabShape(QTabWidget::Triangular);
        GameStudioClass->setDockOptions(QMainWindow::AllowTabbedDocks);
        actionNew_Project = new QAction(GameStudioClass);
        actionNew_Project->setObjectName(QStringLiteral("actionNew_Project"));
        actionOpen_Project = new QAction(GameStudioClass);
        actionOpen_Project->setObjectName(QStringLiteral("actionOpen_Project"));
        actionSave_Project = new QAction(GameStudioClass);
        actionSave_Project->setObjectName(QStringLiteral("actionSave_Project"));
        actionNew_Scene = new QAction(GameStudioClass);
        actionNew_Scene->setObjectName(QStringLiteral("actionNew_Scene"));
        actionOpen_Scene = new QAction(GameStudioClass);
        actionOpen_Scene->setObjectName(QStringLiteral("actionOpen_Scene"));
        actionSave_Scene = new QAction(GameStudioClass);
        actionSave_Scene->setObjectName(QStringLiteral("actionSave_Scene"));
        actionSave_Scene_As = new QAction(GameStudioClass);
        actionSave_Scene_As->setObjectName(QStringLiteral("actionSave_Scene_As"));
        actionExit = new QAction(GameStudioClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionClose_Project = new QAction(GameStudioClass);
        actionClose_Project->setObjectName(QStringLiteral("actionClose_Project"));
        actionEmpty = new QAction(GameStudioClass);
        actionEmpty->setObjectName(QStringLiteral("actionEmpty"));
        centralWidget = new QWidget(GameStudioClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(1);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setStyleSheet(QStringLiteral(""));
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setTabsClosable(false);
        mdiArea->setTabsMovable(true);
        mdiArea->setTabShape(QTabWidget::Triangular);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        GameStudioClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameStudioClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1046, 23));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy);
        menuBar->setAutoFillBackground(false);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuProject = new QMenu(menuBar);
        menuProject->setObjectName(QStringLiteral("menuProject"));
        menuGameObject = new QMenu(menuBar);
        menuGameObject->setObjectName(QStringLiteral("menuGameObject"));
        menuComponent = new QMenu(menuBar);
        menuComponent->setObjectName(QStringLiteral("menuComponent"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        GameStudioClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameStudioClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameStudioClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GameStudioClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameStudioClass->setStatusBar(statusBar);
        dockHierarchy = new QDockWidget(GameStudioClass);
        dockHierarchy->setObjectName(QStringLiteral("dockHierarchy"));
        dockHierarchy->setAutoFillBackground(false);
        dockHierarchy->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockHierarchy->setWidget(dockWidgetContents);
        GameStudioClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockHierarchy);
        dockLog = new QDockWidget(GameStudioClass);
        dockLog->setObjectName(QStringLiteral("dockLog"));
        dockLog->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockLog->setWidget(dockWidgetContents_2);
        GameStudioClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockLog);
        dockInspector = new QDockWidget(GameStudioClass);
        dockInspector->setObjectName(QStringLiteral("dockInspector"));
        dockInspector->setStyleSheet(QLatin1String("*\n"
"{\n"
"	 background-color: rgb(56, 56, 56);\n"
"}"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        dockInspector->setWidget(dockWidgetContents_3);
        GameStudioClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockInspector);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuProject->menuAction());
        menuBar->addAction(menuGameObject->menuAction());
        menuBar->addAction(menuComponent->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project);
        menuFile->addAction(actionClose_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionNew_Scene);
        menuFile->addAction(actionOpen_Scene);
        menuFile->addAction(actionSave_Scene);
        menuFile->addAction(actionSave_Scene_As);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuGameObject->addAction(actionEmpty);
        menuGameObject->addSeparator();
        mainToolBar->addAction(actionNew_Scene);
        mainToolBar->addAction(actionOpen_Scene);
        mainToolBar->addAction(actionSave_Scene);

        retranslateUi(GameStudioClass);
        QObject::connect(actionExit, SIGNAL(triggered()), GameStudioClass, SLOT(close()));

        QMetaObject::connectSlotsByName(GameStudioClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameStudioClass)
    {
        GameStudioClass->setWindowTitle(QApplication::translate("GameStudioClass", "GameStudio", 0));
        actionNew_Project->setText(QApplication::translate("GameStudioClass", "New Project...", 0));
        actionOpen_Project->setText(QApplication::translate("GameStudioClass", "Open Project...", 0));
        actionSave_Project->setText(QApplication::translate("GameStudioClass", "Save Project", 0));
        actionNew_Scene->setText(QApplication::translate("GameStudioClass", "New Scene", 0));
        actionOpen_Scene->setText(QApplication::translate("GameStudioClass", "Open Scene...", 0));
        actionSave_Scene->setText(QApplication::translate("GameStudioClass", "Save Scene", 0));
        actionSave_Scene_As->setText(QApplication::translate("GameStudioClass", "Save Scene As...", 0));
        actionExit->setText(QApplication::translate("GameStudioClass", "Exit", 0));
        actionClose_Project->setText(QApplication::translate("GameStudioClass", "Close Project", 0));
        actionEmpty->setText(QApplication::translate("GameStudioClass", "Empty", 0));
        menuFile->setTitle(QApplication::translate("GameStudioClass", "File", 0));
        menuView->setTitle(QApplication::translate("GameStudioClass", "View", 0));
        menuProject->setTitle(QApplication::translate("GameStudioClass", "Project", 0));
        menuGameObject->setTitle(QApplication::translate("GameStudioClass", "GameObject", 0));
        menuComponent->setTitle(QApplication::translate("GameStudioClass", "Component", 0));
        menuHelp->setTitle(QApplication::translate("GameStudioClass", "Help", 0));
        menuTools->setTitle(QApplication::translate("GameStudioClass", "Tools", 0));
        mainToolBar->setWindowTitle(QApplication::translate("GameStudioClass", "ToolBar", 0));
        dockHierarchy->setWindowTitle(QApplication::translate("GameStudioClass", "Scene Hierarchy", 0));
        dockLog->setWindowTitle(QApplication::translate("GameStudioClass", "Log", 0));
        dockInspector->setWindowTitle(QApplication::translate("GameStudioClass", "Inspector", 0));
    } // retranslateUi

};

namespace Ui {
    class GameStudioClass: public Ui_GameStudioClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESTUDIO_H
