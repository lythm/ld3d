#pragma once
#include "core/EventDispatcher.h"
#include "core/Allocator.h"
#include "core/StdAllocator.h"
#include "core/g_format.h"
#include "utils/Logger.h"


namespace ld3d
{

	class _DLL_CLASS CoreApi : public std::enable_shared_from_this<CoreApi>
	{
	public:

		CoreApi(Logger logger = Logger());
		virtual ~CoreApi(void);


		bool											Initialize(const SysSetting& setting, Allocator* pAlloc = nullptr, DT_CoreApiPtr pDTCore = DT_CoreApiPtr());

		void											Update();

		void											Release();

#ifdef _WIN32
		void											HandleMessage(MSG& msg);
#endif
		TimerManagerPtr									GetTimerManager();

		AssetManagerPtr									GetAssetManager();
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_GraphicsPtr									GetSysGraphics();
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

		bool											LoadPackage(const std::string& packageFile);
		GameObjectPtr									CreateGameObject(const std::string& name);
		GameObjectComponentPtr							CreateGameObjectComponent(const std::string& name);
		GameObjectPtr									CreatGameObjectFromTemplate(const std::string& tpl, const std::string& name);
		GameObjectPtr									Root();

		void											DispatchEvent(EventPtr pEvent);
		EventDispatcher::EventHandlerHandle				AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);
		void											RemoveEventHandler(EventDispatcher::EventHandlerHandle handle);
		ScenePtr										GetScene();
		void											ResetScene();

		RUN_MODE										GetRunMode();
		DT_CoreApiPtr									GetDTCoreApi();

		static Allocator*								GetAllocator();

		static Logger&									logger();

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
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		Sys_SoundPtr									m_pSysSound;
		Sys_TimePtr										m_pSysTime;
		Sys_NetworkPtr									m_pSysNetwork;

		RUN_MODE										m_runmode;

		DT_CoreApiPtr									m_pDTCore;
	};
}
