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

    void setupUi(QMainWindow *GameStudioClass)
    {
        if (GameStudioClass->objectName().isEmpty())
            GameStudioClass->setObjectName(QStringLiteral("GameStudioClass"));
        GameStudioClass->resize(664, 528);
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
        centralWidget = new QWidget(GameStudioClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setTabsClosable(false);
        mdiArea->setTabsMovable(true);
        mdiArea->setTabShape(QTabWidget::Triangular);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        GameStudioClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameStudioClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 664, 23));
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
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockHierarchy->setWidget(dockWidgetContents);
        GameStudioClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockHierarchy);

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
        menuFile->setTitle(QApplication::translate("GameStudioClass", "File", 0));
        menuView->setTitle(QApplication::translate("GameStudioClass", "View", 0));
        menuProject->setTitle(QApplication::translate("GameStudioClass", "Project", 0));
        menuGameObject->setTitle(QApplication::translate("GameStudioClass", "GameObject", 0));
        menuComponent->setTitle(QApplication::translate("GameStudioClass", "Component", 0));
        menuHelp->setTitle(QApplication::translate("GameStudioClass", "Help", 0));
        menuTools->setTitle(QApplication::translate("GameStudioClass", "Tools", 0));
        dockHierarchy->setWindowTitle(QApplication::translate("GameStudioClass", "Scene Hierarchy", 0));
    } // retranslateUi

};

namespace Ui {
    class GameStudioClass: public Ui_GameStudioClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESTUDIO_H
