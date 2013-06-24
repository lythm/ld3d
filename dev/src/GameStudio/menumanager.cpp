#include "stdafx.h"
#include "menumanager.h"
#include "GameEngine.h"
#include "gamestudio.h"

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

	GameObjectManagerPtr pManager = m_pEngine->GetCoreApi()->GetGameObjectManager();

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

}
void MenuManager::UnInstall_Menu_GameObject()
{
	QMenu* pGameObjectMenu = m_pMainWnd->menuGameObject;
	if(pGameObjectMenu)
	{
		pGameObjectMenu->clear();
	}
}
void MenuManager::UnInstall()
{
	UnInstall_Menu_GameObject();
	UnInstall_Menu_Component();
}
void MenuManager::Reset(GameEnginePtr pEngine)
{
	UnInstall();
	m_pEngine = pEngine;

}
void MenuManager::on_menu_gameobject_action()
{
	QAction* pAction = (QAction*)sender();

	ld3d::GameObjectTemplate* pTpl = (ld3d::GameObjectTemplate*)pAction->data().value<void*>();

	if(pTpl == nullptr)
	{
		m_pEngine->CreateObject_Empty();
	}
	else
	{
		m_pEngine->CreateObjectFromTpl(pTpl->GetName(), pTpl->GetName());
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

	GameObjectManagerPtr pManager = m_pEngine->GetCoreApi()->GetGameObjectManager();

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
}
void MenuManager::UnInstall_Menu_Component()
{
	QMenu* pMenu = m_pMainWnd->menuComponent;
	if(pMenu)
	{
		pMenu->clear();
	}
}
void MenuManager::on_menu_component_action()
{
	if(on_action_triggered)
	{
		on_action_triggered();
	}

}
