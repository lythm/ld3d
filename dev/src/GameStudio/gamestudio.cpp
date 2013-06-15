#include "stdafx.h"
#include "gamestudio.h"

GameStudio::GameStudio(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);

	QSettings settings("GGUHA Ltd.", "Game Studio");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

GameStudio::~GameStudio()
{

}
void GameStudio::closeEvent(QCloseEvent *pEvent)
{
	QSettings settings("GGUHA Ltd.", "Game Studio");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());

	QMainWindow::closeEvent(pEvent);
}
