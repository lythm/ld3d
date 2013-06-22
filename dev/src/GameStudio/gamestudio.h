#ifndef GAMESTUDIO_H
#define GAMESTUDIO_H

#include <QtWidgets/QMainWindow>
#include "ui_gamestudio.h"


class Form_Scene;
class Form_Preview;
class Form_Log;
class Form_Inspector;
class Form_Hierarchy;

class GameStudio : public QMainWindow, public Ui::GameStudioClass
{
	Q_OBJECT

public:
	GameStudio(QWidget *parent = 0);
	~GameStudio();

	void							logInfo(const QString& str);
	void							logBuild(const QString& str);
	

	public slots:
	void							on_menuFile_aboutToShow();
	void							on_actionNew_Project_triggered();

	void							on_actionSave_Project_triggered();
	void							on_actionOpen_Project_triggered();
	void							on_mdiArea_subWindowActivated(QMdiSubWindow* pSub);


	Form_Scene*						GetFormScene();
private:
	void							timerEvent(QTimerEvent* e);
	void							showEvent(QShowEvent* e);
	void							closeEvent(QCloseEvent *pEvent);
private:

	Form_Scene*						m_pSceneForm;
	Form_Preview*					m_pPreviewForm;
	Form_Log*						m_pLogForm;
	Form_Inspector*					m_pInspectorForm;
	Form_Hierarchy*					m_pHierarchyForm;


	GameEditorPtr					m_pEditor;
	int								m_updateTimer;
};

#endif // GAMESTUDIO_H
