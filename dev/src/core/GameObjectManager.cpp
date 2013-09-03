#include "core_pch.h"
#include "core/GameObjectManager.h"
#include "core/GameObject.h"

#include "core_utils.h"

#include "core/GameObjectTemplate.h"

namespace ld3d
{
	GameObjectManager::GameObjectManager(void)
	{
	}

	GameObjectManager::~GameObjectManager(void)
	{
	}

	bool GameObjectManager::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		m_componentClasses.clear();
#ifdef _WIN64
		if(false == LoadPackage("./packages/core/package_core_x64.dll"))
		{
			return false;
		}
#else
		if(false == LoadPackage("./package_core_x86.dll"))
		{
			return false;
		}
#endif

		return true;
	}
	void GameObjectManager::Release()
	{
		m_componentClasses.clear();
		
		m_templates.clear();
		for(size_t i = 0; i < m_packages.size(); ++i)
		{
			m_packages[i].delete_package();
		}
		m_packages.clear();
	}
	bool GameObjectManager::LoadAndRegisterTemplate(DataStreamPtr pStream)
	{
		return true;

		/*GameObjectTemplatePtr pTemplate = alloc_object<GameObjectTemplate, GameObjectManagerPtr>(shared_from_this());

		if(pTemplate->Load(pStream) == false)
		{
			return false;
		}

		return RegisterTemplate(pTemplate);*/
	}
	GameObjectPtr GameObjectManager::CreateObjectFromTemplate(const std::string& tpl)
	{
		GameObjectTemplate* pTpl = FindTemplate(tpl);

		if(pTpl == nullptr)
		{
			return GameObjectPtr();
		}

		return pTpl->CreateGameObject();
	}
	bool GameObjectManager::RegisterTemplate(GameObjectTemplate* pTpl)
	{
		std::string name = pTpl->GetName();
		
		if(m_templates.find(name) != m_templates.end())
		{
			return false;
		}
		m_templates[name] = pTpl;
		log("-Template registered: " + name);
		return true;
	}
	
	GameObjectComponentPtr GameObjectManager::CreateComponent(const std::string& name)
	{
		if(m_componentClasses.find(name) == m_componentClasses.end())
		{
			return GameObjectComponentPtr();
		}

		return m_componentClasses[name]->m_creator(shared_from_this());
	}
	
	GameObjectPtr GameObjectManager::CreateGameObject(const std::string& name)
	{
		GameObjectPtr pObj = alloc_object<GameObject>();
		pObj->SetName(name);

		return pObj;
	}
	
	
	bool GameObjectManager::LoadPackage(const std::string& name)
	{
		PackageMod mod;
		if(false == mod.load_package(name.c_str(), shared_from_this()))
		{
			return false;
		}
		
		log(std::string("Loading Package: ") + mod.GetPackage()->GetPackageName());
		RegisterPackage(mod.GetPackage());
		log(std::string("Package loaded: ") + mod.GetPackage()->GetPackageName());
		m_packages.push_back(mod);
		return true;
	}
	int GameObjectManager::GetPackageCount()
	{
		return (int)m_packages.size();
	}
	Package* GameObjectManager::GetPackageByIndex(int index)
	{
		return m_packages[index].GetPackage();
	}
	bool GameObjectManager::RegisterComponentClass(Package::ComponentClass* c)
	{
		if(m_componentClasses.find(c->m_name) != m_componentClasses.end())
		{
			return false;
		}
		m_componentClasses[c->m_name] = c;

		log("-Component registered: " + c->m_name);
		return true;
	}
	bool GameObjectManager::RegisterPackage(Package* pPack)
	{
		for(int i = 0; i < pPack->GetClassCount(); ++i)
		{
			Package::ComponentClass* c = pPack->GetClassByIndex(i);
			RegisterComponentClass(c);
		}

		for(int i = 0; i < pPack->GetTemplateCount(); ++i)
		{
			RegisterTemplate(pPack->GetTemplateByIndex(i));
		}

		return true;
	}
	RenderManagerPtr	GameObjectManager::GetRenderManager()
	{
		return m_pCore->GetRenderManager();
	}
	Allocator* GameObjectManager::GetAllocator()
	{
		return m_pCore->GetAllocator();
	}

	CoreApiPtr GameObjectManager::GetCoreApi()
	{
		return m_pCore;
	}
	GameObjectTemplate* GameObjectManager::FindTemplate(const std::string& name)
	{
		std::unordered_map<std::string, GameObjectTemplate*>::iterator it = m_templates.find(name);

		if(it == m_templates.end())
		{
			return nullptr;
		}

		return it->second;
	}
}


namespace ld3d
{
	GameObjectManager::PackageMod::PackageMod()
	{
		m_pPackage			= nullptr;
		m_hLib				= nullptr;
	}
	Package* GameObjectManager::PackageMod::GetPackage()
	{
		return m_pPackage;
	}
	bool GameObjectManager::PackageMod::load_package(const char* file, GameObjectManagerPtr pManager)
	{
		m_hLib = os_load_module(file);
		if(m_hLib == NULL)
		{
			return false;
		}


		Fn_CreatePackage CreatePackage = (Fn_CreatePackage)os_find_proc(m_hLib, "CreatePackage");
		if(CreatePackage == NULL)
		{
			os_unload_module(m_hLib);
			return false;
		}

		m_file = file;
		m_pPackage = CreatePackage(pManager);

		return true;
	}

	void GameObjectManager::PackageMod::delete_package()
	{
		if(m_hLib == NULL)
		{
			return;
		}
		Fn_DestroyPackage DestroyPackage = (Fn_DestroyPackage)os_find_proc(m_hLib, "DestroyPackage");

		if(DestroyPackage == NULL)
		{
			return;

		}
		m_pPackage->Release();

		DestroyPackage(m_pPackage);

		os_unload_module(m_hLib);
		m_hLib = NULL;
	}
	void GameObjectManager::Log(const std::string& text)
	{
		log(text);
	}
	Sys_SoundPtr GameObjectManager::GetSysSound()
	{
		return m_pCore->GetSysSound();
	}
	AssetManagerPtr GameObjectManager::GetAssetManager()
	{
		return m_pCore->GetAssetManager();
	}
	void GameObjectManager::DispatchEvent(EventPtr pEvent)
	{
		m_pCore->DispatchEvent(pEvent);
	}
	EventDispatcher::EventHandlerHandle GameObjectManager::AddEventHandler(uint32 id, EventDispatcher::EventHandler handler)
	{
		return m_pCore->AddEventHandler(id, handler);
	}
	void GameObjectManager::RemoveEventHandler(EventDispatcher::EventHandlerHandle handle)
	{
		m_pCore->RemoveEventHandler(handle);
	}
	RUN_MODE GameObjectManager::GetRunMode()
	{
		return m_pCore->GetRunMode();
	}
	DT_CoreApiPtr GameObjectManager::GetDTCoreApi()
	{
		return m_pCore->GetDTCoreApi();
	}
}
