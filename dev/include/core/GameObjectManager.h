#pragma once

#include "core\ExtPackage.h"

#include <boost\enable_shared_from_this.hpp>
#include "core\EventDispatcher.h"

namespace ld3d
{
	class Allocator;

	class EXPORT_CLASS GameObjectManager : public boost::enable_shared_from_this<GameObjectManager>
	{
		class PackageMod
		{
		public:
			PackageMod();
			typedef ExtPackage*					(*Fn_CreatePackage)(CoreApiPtr pCore);
			typedef void						(*Fn_DestroyPackage)(ExtPackage*);

			bool								load_package(const wchar_t* file, CoreApiPtr pCore);
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
	private:


	private:
		boost::unordered_map<std::wstring, GameObjectTemplate*>				m_templates;
		boost::unordered_map<std::wstring, ExtPackage::ComponentClass*>		m_componentClasses;

		std::vector<PackageMod>												m_packages;
		CoreApiPtr															m_pCore;
	};
}
