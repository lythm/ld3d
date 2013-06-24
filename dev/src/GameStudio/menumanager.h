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

	void														Install();
	void														UnInstall();
	void														Reset(GameEnginePtr pEngine);


	std::function<void()>										on_action_triggered;
public slots:
	void														on_menu_gameobject_action();
	void														on_menu_component_action();
private:
	void														Install_Menu_GameObject();
	void														UnInstall_Menu_GameObject();

	void														Install_Menu_Component();
	void														UnInstall_Menu_Component();
private:

	GameStudio*													m_pMainWnd;
	GameEnginePtr												m_pEngine;
	
};

#endif // MENUMANAGER_H
