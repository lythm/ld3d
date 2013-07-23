#include "stdafx.h"
#include "menumanager.h"
#include "GameEngine.h"
#include "gamestudio.h"
#include "GameEditor.h"

MenuManager::MenuManager(QObject *parent)
	: QObject(parent)
{
	m_pMainWnd = (GameStudio*)parent;
}

MenuManager::~MenuManager()
{

}
void MenuManager::Clear()
{
	UnInstall_MainMenu();
}
void MenuManager::Install_MainMenu()
{
	UnInstall_MainMenu();

	QMenu* pMenu = m_pMainWnd->menuGameObject;
	pMenu->clear();
	Install_Menu_GameObject(pMenu);
	pMenu->menuAction()->setVisible(true);


	pMenu = m_pMainWnd->menuComponent;
	pMenu->clear();
	Install_Menu_Component(pMenu);
	pMenu->menuAction()->setVisible(true);

}
void MenuManager::Install_Menu_GameObject(QMenu* pMenu)
{
	using namespace ld3d;

	connect(pMenu->addAction("Empty"), SIGNAL(triggered()), this, SLOT(on_menu_gameobject_action()));

	pMenu->addSeparator();
	

	std::unordered_map<std::wstring, std::vector<ld3d::GameObjectTemplate*> >			tplMap;

	GameObjectManagerPtr pManager = m_pEditor->GetGameEngine()->GetCoreApi()->GetGameObjectManager();

	for(size_t i = 0; i < pManager->GetPackageCount(); ++i)
	{
		Package* pPack = pManager->GetPackageByIndex(i);
		for(size_t ii = 0; ii < pPack->GetTemplateCount(); ++ii)
		{
			GameObjectTemplate* pTpl = pPack->GetTemplateByIndex(ii);

			tplMap[pTpl->GetCataLog()].push_back(pTpl);
		}
	}

	for(auto v : tplMap)
	{
		if(v.second.size() == 0)
		{
			continue;
		}
		
		QString subName = QString::fromStdWString(v.first);
		QMenu* pSub = pMenu->addMenu(subName);

		
		for(size_t i = 0; i < v.second.size(); ++i)
		{
			QString name = QString::fromStdWString(v.second[i]->GetName());

			QAction* pAction = pSub->addAction(name);
			pAction->setData(qVariantFromValue((void*)v.second[i]));

			connect(pAction, SIGNAL(triggered()), this, SLOT(on_menu_gameobject_action()));
		}
	}
}

void MenuManager::UnInstall_MainMenu()
{
	QMenu* pMenu = m_pMainWnd->menuGameObject;
	if(pMenu)
	{
		pMenu->clear();
		pMenu->menuAction()->setVisible(false);
	}

	pMenu = m_pMainWnd->menuComponent;
	if(pMenu)
	{
		pMenu->clear();
		pMenu->menuAction()->setVisible(false);
	}
}
void MenuManager::Reset(GameEditorPtr pEditor)
{
	UnInstall_MainMenu();
	m_pEditor = pEditor;
	Install_MainMenu();
}
void MenuManager::on_menu_gameobject_action()
{
	QAction* pAction = (QAction*)sender();

	ld3d::GameObjectTemplate* pTpl = (ld3d::GameObjectTemplate*)pAction->data().value<void*>();

	if(pTpl == nullptr)
	{
		m_pEditor->GetGameEngine()->CreateObject_Empty();
	}
	else
	{
		m_pEditor->GetGameEngine()->CreateObjectFromTpl(pTpl->GetName(), pTpl->GetName());
	}
	
	if(on_action_triggered)
	{
		on_action_triggered();
	}
}


void MenuManager::Install_Menu_Component(QMenu* pMenu)
{
	using namespace ld3d;

	std::unordered_map<std::wstring, std::vector<ld3d::Package::ComponentClass*> >	comMap;

	GameObjectManagerPtr pManager = m_pEditor->GetGameEngine()->GetCoreApi()->GetGameObjectManager();

	for(size_t i = 0; i < pManager->GetPackageCount(); ++i)
	{
		Package* pPack = pManager->GetPackageByIndex(i);
		for(size_t ii = 0; ii < pPack->GetClassCount(); ++ii)
		{
			Package::ComponentClass* pClass = pPack->GetClassByIndex(ii);

			if(pClass->m_name == L"PropertyManager")
			{
				continue;
			}
			if(pClass->m_catalog == L"DT")
			{
				continue;
			}
			comMap[pClass->m_catalog].push_back(pClass);
		}
	}
	
	for(auto v : comMap)
	{
		if(v.second.size() == 0)
		{
			continue;
		}
		
		QString subName = QString::fromStdWString(v.first);
		QMenu* pSub = pMenu->addMenu(subName);

		
		for(size_t i = 0; i < v.second.size(); ++i)
		{
			QString name = QString::fromStdWString(v.second[i]->m_name);

			QAction* pAction = pSub->addAction(name);
			pAction->setData(qVariantFromValue((void*)v.second[i]));

			connect(pAction, SIGNAL(triggered()), this, SLOT(on_menu_component_action()));
		}
	}

	connect(pMenu, SIGNAL(aboutToShow()), this, SLOT(on_menu_component_aboutToShow()));
	pMenu->menuAction()->setVisible(true);
}

void MenuManager::on_menu_component_action()
{
	if(on_action_triggered)
	{
		on_action_triggered();
	}

}
void MenuManager::on_menu_gameobject_aboutToShow()
{
}
void MenuManager::on_menu_component_aboutToShow()
{
	QMenu* pMenu = (QMenu*)sender();

	QList<QAction*> actions = pMenu->actions();

	for(int i = 0; i < actions.count(); ++i)
	{
		actions.at(i)->setEnabled(m_pEditor->GetCurrentObject() != nullptr);
	}
}
