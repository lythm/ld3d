#ifndef GAMESTUDIO_H
#define GAMESTUDIO_H

#include <QtWidgets/QMainWindow>
#include "ui_gamestudio.h"


class Form_Scene;
class Form_Preview;

class GameStudio : public QMainWindow, public Ui::GameStudioClass
{
	Q_OBJECT

public:
	GameStudio(QWidget *parent = 0);
	~GameStudio();

	bool event(QEvent *event);
	void closeEvent(QCloseEvent *pEvent);


private:

	Form_Scene*						m_pSceneForm;
	Form_Preview*					m_pPreviewForm;
};

#endif // GAMESTUDIO_H
