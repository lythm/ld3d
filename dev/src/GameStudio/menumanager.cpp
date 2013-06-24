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

void MenuManager::Install()
{
	UnInstall();

	Install_Menu_GameObject();
	Install_Menu_Component();
}
void MenuManager::Install_Menu_GameObject()
{
	QMenu* pGameObjectMenu = m_pMainWnd->menuGameObject;

	using namespace ld3d;

	pGameObjectMenu->clear();

	
	connect(pGameObjectMenu->addAction("Empty"), SIGNAL(triggered()), this, SLOT(on_menu_gameobject_action()));

	pGameObjectMenu->addSeparator();
	

	std::unordered_map<std::wstring, std::vector<ld3d::GameObjectTemplate*> >			tplMap;

	GameObjectManagerPtr pManager = m_pEditor->GetGameEngine()->GetCoreApi()->GetGameObjectManager();

	for(size_t i = 0; i < pManager->GetPackageCount(); ++i)
	{
		ExtPackage* pPack = pManager->GetPackageByIndex(i);
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
		QMenu* pSub = pGameObjectMenu->addMenu(subName);

		
		for(size_t i = 0; i < v.second.size(); ++i)
		{
			QString name = QString::fromStdWString(v.second[i]->GetName());

			QAction* pAction = pSub->addAction(name);
			pAction->setData(qVariantFromValue((void*)v.second[i]));

			connect(pAction, SIGNAL(triggered()), this, SLOT(on_menu_gameobject_action()));
		}
	}
	pGameObjectMenu->menuAction()->setVisible(true);
}
void MenuManager::UnInstall_Menu_GameObject()
{
	QMenu* pGameObjectMenu = m_pMainWnd->menuGameObject;
	if(pGameObjectMenu)
	{
		pGameObjectMenu->clear();
		pGameObjectMenu->menuAction()->setVisible(false);
	}
}
void MenuManager::UnInstall()
{
	UnInstall_Menu_GameObject();
	UnInstall_Menu_Component();
}
void MenuManager::Reset(GameEditorPtr pEditor)
{
	UnInstall();
	m_pEditor = pEditor;

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


void MenuManager::Install_Menu_Component()
{
	using namespace ld3d;

	std::unordered_map<std::wstring, std::vector<ld3d::ExtPackage::ComponentClass*> >	comMap;

	GameObjectManagerPtr pManager = m_pEditor->GetGameEngine()->GetCoreApi()->GetGameObjectManager();

	for(size_t i = 0; i < pManager->GetPackageCount(); ++i)
	{
		ExtPackage* pPack = pManager->GetPackageByIndex(i);
		for(size_t ii = 0; ii < pPack->GetClassCount(); ++ii)
		{
			ExtPackage::ComponentClass* pClass = pPack->GetClassByIndex(ii);

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
	
	QMenu* pMenu = m_pMainWnd->menuComponent;
	pMenu->clear();

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
void MenuManager::UnInstall_Menu_Component()
{
	QMenu* pMenu = m_pMainWnd->menuComponent;
	if(pMenu)
	{
		pMenu->clear();
		pMenu->disconnect(SIGNAL(aboutToShow()));
	}
	pMenu->menuAction()->setVisible(false);
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
