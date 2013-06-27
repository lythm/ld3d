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
	

	void							on_idle();

	
	public slots:

	void							on_menuFile_aboutToShow();
	void							on_actionNew_Project_triggered();
	void							on_actionClose_Project_triggered();
	void							on_actionSave_Project_triggered();
	void							on_actionOpen_Project_triggered();
	void							on_mdiArea_subWindowActivated(QMdiSubWindow* pSub);
	void							on_actionNew_Scene_triggered();
	void							on_actionSave_Scene_triggered();
	void							on_actionSave_Scene_As_triggered();
	void							on_actionOpen_Scene_triggered();
	

	Form_Scene*						GetFormScene();
	Form_Hierarchy*					GetFormHierarchy();
	Form_Inspector*					GetFormInspector();
private:
	void							showEvent(QShowEvent* e);
	void							closeEvent(QCloseEvent *pEvent);

	bool							SaveSceneAs();
	bool							SaveScene();

	void							UpdateActions();
private:

	Form_Scene*						m_pSceneForm;
	Form_Preview*					m_pPreviewForm;
	Form_Log*						m_pLogForm;
	Form_Inspector*					m_pInspectorForm;
	Form_Hierarchy*					m_pHierarchyForm;


	GameEditorPtr					m_pEditor;
};

#endif // GAMESTUDIO_H
