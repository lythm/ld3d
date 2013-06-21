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

	bool							event(QEvent *event);
	void							closeEvent(QCloseEvent *pEvent);


	void							logInfo(const QString& str);
	void							logBuild(const QString& str);
	

	public slots:
	void							on_menufile_abouttoshow();
	void							on_actionNew_Project_triggered();

	void							on_actionSave_Project_triggered();
	void							on_actionOpen_Project_triggered();
	void							on_mdiArea_subWindowActivated(QMdiSubWindow* pSub);
private:

	Form_Scene*						m_pSceneForm;
	Form_Preview*					m_pPreviewForm;
	Form_Log*						m_pLogForm;
	Form_Inspector*					m_pInspectorForm;
	Form_Hierarchy*					m_pHierarchyForm;


	ProjectPtr						m_pProject;
};

#endif // GAMESTUDIO_H
