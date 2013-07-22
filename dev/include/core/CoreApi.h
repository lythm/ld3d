#pragma once
#include "core\EventDispatcher.h"
#include "core\Allocator.h"
#include "core\StdAllocator.h"
#include "core\g_format.h"


namespace ld3d
{
	
	class EXPORT_CLASS CoreApi : public std::enable_shared_from_this<CoreApi>
	{
	public:
		typedef std::function<void (const std::wstring& log)>			Logger;

		CoreApi(void);
		virtual ~CoreApi(void);


		bool											Initialize(const SysSetting& setting, Allocator* pAlloc = nullptr, DT_CoreApiPtr pDTCore = DT_CoreApiPtr());

		void											Update();
		
		void											Release();
		void											HandleMessage(MSG& msg);
		
		TimerManagerPtr									GetTimerManager();

		AssetManagerPtr									GetAssetManager();
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_Graphics2Ptr								GetSysGraphics();
		Sys_InputPtr									GetSysInput();
		Sys_SoundPtr									GetSysSound();
		Sys_TimePtr										GetSysTime();

		void											Render();
		void											Render(CameraPtr pCamera);
		void											Present();
		void											AddRenderData(RenderDataPtr pData);
		void											ClearRenderQueue();
		
		void											AddCamera(CameraPtr pCamera);
		void											RemoveCamera(CameraPtr pCamera);

		RenderManagerPtr								GetRenderManager();

		bool											LoadPackage(const std::wstring& packageFile);
		GameObjectPtr									CreateGameObject(const std::wstring& name);
		GameObjectComponentPtr							CreateGameObjectComponent(const std::wstring& name);
		GameObjectPtr									CreatGameObjectFromTemplate(const std::wstring& tpl, const std::wstring& name);
		GameObjectPtr									Root();

		void											DispatchEvent(EventPtr pEvent);
		EventDispatcher::EventHandlerHandle				AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);
		void											RemoveEventHandler(EventDispatcher::EventHandlerHandle handle);
		ScenePtr										GetScene();
		void											ResetScene();

		RUN_MODE										GetRunMode();
		DT_CoreApiPtr									GetDTCoreApi();

		static Allocator*								GetAllocator();

		static void										Log(const std::wstring& text);
		static void										SetLogger(Logger logger);

	private:
		GameObjectManagerPtr							m_pObjectManager;
		EventDispatcherPtr								m_pEventDispatcher;
		AssetManagerPtr									m_pAssetManager;

		RenderManagerPtr								m_pRenderManager;

		static Allocator*								s_pAllocator;
		static Logger									s_logger;
		ScenePtr										m_pScene;

		TimerManagerPtr									m_pTimerManager;

		float											m_lastFrameTime;

		SysManagerPtr									m_pSysManager;
		Sys_Graphics2Ptr								m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		Sys_SoundPtr									m_pSysSound;
		Sys_TimePtr										m_pSysTime;
		Sys_NetworkPtr									m_pSysNetwork;

		RUN_MODE										m_runmode;

		DT_CoreApiPtr									m_pDTCore;
	};
}
