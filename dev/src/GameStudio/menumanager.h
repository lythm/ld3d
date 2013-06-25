#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QObject>

class GameStudio;

class MenuManager : public QObject
{
	Q_OBJECT

public:
	MenuManager(QObject *parent);
	~MenuManager();

	
	void														Reset(GameEditorPtr pEditor);

	void														Clear();

	std::function<void()>										on_action_triggered;
public slots:
	void														on_menu_gameobject_action();
	void														on_menu_component_action();
	void														on_menu_gameobject_aboutToShow();
	void														on_menu_component_aboutToShow();
private:
	void														Install_Menu_GameObject(QMenu* pMenu);
	void														Install_Menu_Component(QMenu* pMenu);
	void														Install_MainMenu();
	void														UnInstall_MainMenu();
private:

	GameStudio*													m_pMainWnd;
	GameEditorPtr												m_pEditor;

};

#endif // MENUMANAGER_H
