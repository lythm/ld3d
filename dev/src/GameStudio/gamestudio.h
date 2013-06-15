#ifndef GAMESTUDIO_H
#define GAMESTUDIO_H

#include <QtWidgets/QMainWindow>
#include "ui_gamestudio.h"

class GameStudio : public QMainWindow, public Ui::GameStudioClass
{
	Q_OBJECT

public:
	GameStudio(QWidget *parent = 0);
	~GameStudio();


	void closeEvent(QCloseEvent *pEvent);
private:

};

#endif // GAMESTUDIO_H
