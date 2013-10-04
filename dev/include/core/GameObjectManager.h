#pragma once

#include "core/Package.h"

#include <boost/enable_shared_from_this.hpp>
#include "core/EventDispatcher.h"
#include "core/CoreApi.h"
namespace ld3d
{
	class Allocator;

	class _DLL_CLASS GameObjectManager : public std::enable_shared_from_this<GameObjectManager>
	{
		class PackageMod
		{
		public:
			PackageMod();
			typedef Package*					(*Fn_CreatePackage)(GameObjectManagerPtr);
			typedef void						(*Fn_DestroyPackage)(Package*);

			bool								load_package(const char* file, GameObjectManagerPtr pManager);
			void								delete_package();

			Package*							GetPackage();

		private:
			Package*							m_pPackage;
			void*								m_hLib;
			std::string							m_file;
		};

	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);

		bool																Initialize(CoreApiPtr pCore);
		void																Release();

		bool																LoadPackage(const std::string& name);
		

		GameObjectPtr														CreateGameObject(const std::string& name);
		GameObjectPtr														CreateObjectFromTemplate(const std::string& tpl);

		bool																RegisterTemplate(GameObjectTemplate* pTpl);

		GameObjectComponentPtr												CreateComponent(const std::string& name);

		int																	GetPackageCount();
		Package*															GetPackageByIndex(int index);

		bool																RegisterPackage(Package* pPack);
		bool																RegisterComponentClass(Package::ComponentClass* c);

		RenderManagerPtr													GetRenderManager();

		Allocator*															GetAllocator();
		CoreApiPtr															GetCoreApi();

		GameObjectTemplate*													FindTemplate(const std::string& name);

		bool																LoadAndRegisterTemplate(DataStreamPtr pStream);

		Sys_SoundPtr														GetSysSound();

		Logger&																logger();

		AssetManagerPtr														GetAssetManager();

		void																DispatchEvent(EventPtr pEvent);
		EventHandlerID														AddEventHandler(uint32 id, EventHandler handler);
		void																RemoveEventHandler(EventHandlerID handle);

		RUN_MODE															GetRunMode();

		DT_CoreApiPtr														GetDTCoreApi();

		template<typename T> inline
			std::shared_ptr<T>												alloc_object()
		{
			return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator());
		}

		template<typename T, typename TP> inline
			std::shared_ptr<T>												alloc_object(TP& p)
		{
			return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator(), p);
		}
	private:

		bool																LoadNativePackage(const std::string& name);
		bool																LoadLuaPackage(const std::string& name);
	private:
		std::unordered_map<std::string, GameObjectTemplate*>				m_templates;
		std::unordered_map<std::string, Package::ComponentClass*>		m_componentClasses;

		std::vector<PackageMod>												m_packages;
		CoreApiPtr															m_pCore;
	};
}
