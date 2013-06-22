#pragma once

#include "core\ExtPackage.h"

#include <boost\enable_shared_from_this.hpp>
#include "core\EventDispatcher.h"
#include "core/CoreApi.h"
namespace ld3d
{
	class Allocator;

	class EXPORT_CLASS GameObjectManager : public std::enable_shared_from_this<GameObjectManager>
	{
		class PackageMod
		{
		public:
			PackageMod();
			typedef ExtPackage*					(*Fn_CreatePackage)(GameObjectManagerPtr);
			typedef void						(*Fn_DestroyPackage)(ExtPackage*);

			bool								load_package(const wchar_t* file, GameObjectManagerPtr pManager);
			void								delete_package();

			ExtPackage*							GetPackage();

		private:
			ExtPackage*							m_pPackage;
			HMODULE								m_hLib;
			std::wstring						m_file;
		};

	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);

		bool																Initialize(CoreApiPtr pCore);
		void																Release();

		bool																LoadPackage(const std::wstring& name);

		GameObjectPtr														CreateGameObject(const std::wstring& name);
		GameObjectPtr														CreateObjectFromTemplate(const std::wstring& tpl);

		bool																RegisterTemplate(GameObjectTemplate* pTpl);

		GameObjectComponentPtr												CreateComponent(const std::wstring& name);

		int																	GetPackageCount();
		ExtPackage*															GetPackageByIndex(int index);

		bool																RegisterPackage(ExtPackage* pPack);
		bool																RegisterComponentClass(ExtPackage::ComponentClass* c);

		RenderManagerPtr													GetRenderManager();

		Allocator*															GetAllocator();
		CoreApiPtr															GetCoreApi();

		GameObjectTemplate*													FindTemplate(const std::wstring& name);

		bool																LoadAndRegisterTemplate(DataStreamPtr pStream);

		Sys_SoundPtr														GetSysSound();

		void																Log(const std::wstring& text);

		AssetManagerPtr														GetAssetManager();

		void																DispatchEvent(EventPtr pEvent);
		EventDispatcher::EventHandlerHandle									AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);
		void																RemoveEventHandler(EventDispatcher::EventHandlerHandle handle);

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


	private:
		std::unordered_map<std::wstring, GameObjectTemplate*>				m_templates;
		std::unordered_map<std::wstring, ExtPackage::ComponentClass*>		m_componentClasses;

		std::vector<PackageMod>												m_packages;
		CoreApiPtr															m_pCore;
	};
}
