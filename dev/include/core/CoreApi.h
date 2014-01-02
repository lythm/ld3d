#pragma once
#include "core/EventDispatcher.h"
#include "core/Allocator.h"
#include "core/StdAllocator.h"
#include "utils/Logger.h"
#include "core/SysSettings.h"

#include "core/FrameMetric.h"


namespace ld3d
{
	class Console;

	class _DLL_CLASS CoreApi : public std::enable_shared_from_this<CoreApi>
	{
	public:

		CoreApi(Logger logger = Logger());
		virtual ~CoreApi(void);


		bool											Initialize(const SysSetting& setting, Allocator* pAlloc = nullptr, DT_CoreApiPtr pDTCore = DT_CoreApiPtr());

		void											RunFrame();

		bool											LoadMod(const std::string& name);

		void											Release();


		void											QuitApp();

#ifdef _WIN32
		void											HandleMessage(MSG& msg);
#endif
		TimerManagerPtr									GetTimerManager();
		PhysicsManagerPtr								GetPhysicsManager();
		AssetManagerPtr									GetAssetManager();
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_GraphicsPtr									GetSysGraphics();
		Sys_InputPtr									GetSysInput();
		Sys_SoundPtr									GetSysSound();
		Sys_TimePtr										GetSysTime();

		UIManagerPtr									GetUIManager();

		void											Render();
		void											Render(CameraPtr pCamera);
		void											Present();
		void											AddRenderData(LAYER layer, RenderDataPtr pData);
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
		EventHandlerID									AddEventHandler(uint32 id, EventHandler handler);
		void											RemoveEventHandler(EventHandlerID handle);
		ScenePtr										GetScene();
		void											ResetScene();

		RUN_MODE										GetRunMode();
		DT_CoreApiPtr									GetDTCoreApi();

		static Allocator*								GetAllocator();

		static Logger&									logger();


		AppDelegate										app_delegate;

		const FrameMetric&								GetFrameMetric();

		void*											GetMainWndHandle();

		void											ShowConsole(bool show);
	private:
		void											UpdateFrame(float dt);
		void											RenderFrame();

		void											UpdateFPS();
	private:

		UIManagerPtr									m_pUIManager;

		GameObjectManagerPtr							m_pObjectManager;
		EventDispatcherPtr								m_pEventDispatcher;
		AssetManagerPtr									m_pAssetManager;

		RenderManagerPtr								m_pRenderManager;

		static Allocator*								s_pAllocator;
		static Logger									s_logger;
		ScenePtr										m_pScene;

		TimerManagerPtr									m_pTimerManager;

		float											m_lastFrameTime;

		PhysicsManagerPtr								m_pPhysicsManager;

		SysManagerPtr									m_pSysManager;
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		Sys_SoundPtr									m_pSysSound;
		Sys_TimePtr										m_pSysTime;
		Sys_NetworkPtr									m_pSysNetwork;

		RUN_MODE										m_runmode;

		DT_CoreApiPtr									m_pDTCore;

		GameManagerPtr									m_pGameManager;

		FrameMetric										m_frameMetric;

		void*											m_mainWndHandle;

		std::shared_ptr<Console>						m_pConsole;
	};
}
