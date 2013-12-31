#include "core_pch.h"
#include "core/CoreApi.h"

#include "core/SysManager.h"
#include "core/Sys_Graphics.h"
#include "core/Sys_Network.h"
#include "core/GameObjectManager.h"
#include "core/RenderManager.h"
#include "core/AssetsManager.h"
#include "core/TimerManager.h"
#include "core/UIManager.h"
#include "core/PhysicsManager.h"



#include "core/Event.h"
#include "core/PoolAllocator.h"
#include "core/StdAllocator.h"
#include "core/Scene.h"

#include "core/GameObject.h"

#include "WinRawInput.h"

#include "core/Sys_Sound.h"
#include "core_utils.h"

#include "Time64.h"

#include "core/Event.h"
#include "GameManager.h"

namespace ld3d
{
	Allocator*										CoreApi::s_pAllocator;
	Logger											CoreApi::s_logger = Logger();
	static StdAllocator								g_stdAllocator;

	CoreApi::CoreApi(Logger logger)
	{
		m_runmode					= RM_RT;
		s_logger					= logger;

		m_mainWndHandle				= nullptr;
	}


	CoreApi::~CoreApi(void)
	{
	}
	void CoreApi::RunFrame()
	{
		m_frameMetric.BeginFrame();

		float frame_step = 1.0f / 30.0f;

		m_pSysTime->Update();

		float dt = m_pSysTime->Second() - m_lastFrameTime;
		m_lastFrameTime = m_pSysTime->Second();

		while(dt > frame_step)
		{
			UpdateFrame(frame_step);
			dt -= frame_step;
		}

		UpdateFrame(dt);

		RenderFrame();

		m_frameMetric.EndFrame();

		UpdateFPS();
	}
	bool CoreApi::LoadMod(const std::string& name)
	{
		return m_pGameManager->Initialize(shared_from_this(), name);
	}
	void CoreApi::UpdateFrame(float dt)
	{
		s_pAllocator->Update();
		m_pTimerManager->Update();

		m_pSysNetwork->Update();
		m_pSysInput->Update();

		m_pSysSound->Update();

		m_pUIManager->Update(dt);

		m_pScene->Update(dt);

		m_pPhysicsManager->Update(dt);

		m_pGameManager->Update(dt);

	}
	void CoreApi::RenderFrame()
	{
		m_pUIManager->PrepareForRendering();

		Render();
		ClearRenderQueue();
		Present();
	}
	bool CoreApi::Initialize(const SysSetting& setting, Allocator* pAlloc, DT_CoreApiPtr pDTCore)
	{
		m_mainWndHandle				= setting.main_wnd;
		app_delegate				= setting.app_delegate;
		m_pDTCore					= pDTCore;
		m_runmode					= m_pDTCore == nullptr ? RM_RT : RM_DT;
		s_pAllocator				= pAlloc;

		if(s_pAllocator == nullptr)
		{
			s_pAllocator = &g_stdAllocator;
		}
		m_pSysTime = alloc_object<Time64>();
		m_pSysTime->Start();
		m_pEventDispatcher = alloc_object<EventDispatcher>();
		m_pSysManager = alloc_object<SysManager>();
		m_pSysGraphics = m_pSysManager->LoadSysGraphics(setting.graphics.sysMod.c_str());
		
		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(setting.graphics))
		{
			return false;
		}

#if defined(_WIN64) || defined(_WIN32)
		m_pSysInput = alloc_object<WinRawInput>();
#endif
        
#ifdef __APPLE__
        m_pSysInput = nullptr;
#endif
		if(false == m_pSysInput->Initialize(setting.input.wnd, std::bind(&CoreApi::DispatchEvent, this, std::placeholders::_1)))
		{
			return false;
		}

		m_pSysSound = m_pSysManager->LoadSysSound(setting.sound.sysMod.c_str());
		if(m_pSysSound->Initialize(100) == false)
		{
			return false;
		}

		m_pSysNetwork = m_pSysManager->LoadSysNetwork(setting.network.sysMod.c_str());
		if(m_pSysNetwork->Initialize() == false)
		{
			return false;
		}


		m_pPhysicsManager = alloc_object<PhysicsManager>();
		if(m_pPhysicsManager->Initialize() == false)
		{
			return false;
		}

		m_pTimerManager = alloc_object<TimerManager>();

		if(m_pTimerManager->Init(m_pSysTime) == false)
		{
			return false;
		}

		m_pAssetManager = alloc_object<AssetManager>();
		if(m_pAssetManager->Initialize(m_pSysGraphics, m_pSysSound) == false)
		{
			return false;
		}

		m_pRenderManager = alloc_object<RenderManager>();
		if(m_pRenderManager->Initialize(m_pSysGraphics, m_pEventDispatcher) == false)
		{
			return false;
		}
		
		m_pUIManager	= alloc_object<UIManager>();
		if(m_pUIManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}
		

		m_pObjectManager = alloc_object<GameObjectManager>();
		if(m_pObjectManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}


		for(auto package : setting.packages)
		{
			if(m_pObjectManager->LoadPackage(package) == false)
			{
				return false;
			}
		}

		m_pScene = alloc_object<Scene>(m_pObjectManager);


		m_pGameManager = alloc_object<GameManager>();

		if(false == LoadMod(setting.mod))
		{
			return false;
		}
				
		m_lastFrameTime = m_pSysTime->Second();


		EventPtr pEvent = alloc_object<Event, uint32>(EV_ENGINE_INITIALIZED);

		DispatchEvent(pEvent);

		return true;
	}


	void CoreApi::Release()
	{
		EventPtr pEvent = alloc_object<Event, uint32>(EV_ENGINE_ABOUT_TO_RELEASE);

		DispatchEvent(pEvent);

		pEvent.reset();


		_release_and_reset(m_pGameManager);

		_release_and_reset(m_pScene);

		if(m_pEventDispatcher)
		{
			m_pEventDispatcher->Clear();
			m_pEventDispatcher.reset();
		}

		_release_and_reset(m_pObjectManager);

		_release_and_reset(m_pUIManager);

		_release_and_reset(m_pRenderManager);

		_release_and_reset(m_pAssetManager);

		_release_and_reset(m_pTimerManager);
		
		_release_and_reset(m_pPhysicsManager);

		_release_and_reset(m_pSysNetwork);

		_release_and_reset(m_pSysInput);
		
		_release_and_reset(m_pSysGraphics);

		_release_and_reset(m_pSysSound);
		
		m_pSysManager.reset();
		
		if(m_pSysTime)
		{
			m_pSysTime->Stop();
			m_pSysTime.reset();
		}
		s_pAllocator	= nullptr;
	}

	GameObjectManagerPtr CoreApi::GetGameObjectManager()
	{
		return m_pObjectManager;
	}
	Sys_GraphicsPtr	CoreApi::GetSysGraphics()
	{
		return m_pSysGraphics;
	}
	Sys_InputPtr CoreApi::GetSysInput()
	{
		return m_pSysInput;
	}
    
#ifdef _WIN32
	void CoreApi::HandleMessage(MSG& msg)
	{
		std::shared_ptr<Event_WindowMessage> pEvent = alloc_object<Event_WindowMessage>(msg);
		pEvent->msg = msg;

		DispatchEvent(pEvent);

		if(m_pSysInput)
		{
			m_pSysInput->HandleMessage(msg);
		}
	}
#endif
	void CoreApi::Render()
	{
		if(m_pRenderManager)
		{
			m_pRenderManager->Render();
		}
	}
	void CoreApi::Render(CameraPtr pCamera)
	{
		if(m_pRenderManager)
		{
			m_pRenderManager->Render(pCamera);
		}
	}
	void CoreApi::AddRenderData(LAYER layer, RenderDataPtr pData)
	{
		if(m_pRenderManager)
		{
			m_pRenderManager->AddRenderData(layer, pData);
		}
	}
	void CoreApi::ClearRenderQueue()
	{
		if(m_pRenderManager)
		{
			m_pRenderManager->Clear();
		}
	}
	RenderManagerPtr	CoreApi::GetRenderManager()
	{
		return m_pRenderManager;
	}
	GameObjectPtr CoreApi::CreateGameObject(const std::string& name)
	{
		GameObjectPtr pObj = m_pObjectManager->CreateGameObject(name);
		pObj->LinkTo(m_pScene->Root());

		return pObj;
	}
	GameObjectPtr CoreApi::CreatGameObjectFromTemplate(const std::string& tpl, const std::string& name)
	{
		GameObjectPtr pObj = m_pObjectManager->CreateObjectFromTemplate(tpl);

		if(pObj == nullptr)
		{
			return GameObjectPtr();
		}
		if(name != "")
		{
			pObj->SetName(name);
		}

		pObj->LinkTo(m_pScene->Root());
		return pObj;

	}
	GameObjectPtr CoreApi::Root()
	{
		return m_pScene->Root();
	}
	GameObjectComponentPtr CoreApi::CreateGameObjectComponent(const std::string& name)
	{
		return m_pObjectManager->CreateComponent(name);
	}
	void CoreApi::DispatchEvent(EventPtr pEvent)
	{
		switch(pEvent->id)
		{
		case EV_KEYBOARD_STATE:
		case EV_MOUSE_MOVE:
		case EV_MOUSE_WHEEL:
		case EV_MOUSE_BUTTON:
		case EV_CHAR:

			if(m_pUIManager->DispatchInputEvent(pEvent) == false)
			{
				return;
			}
			break;

		default:
			break;
		}

		m_pEventDispatcher->DispatchEvent(pEvent);
	}
	EventHandlerID CoreApi::AddEventHandler(uint32 id, EventHandler handler)
	{
		return m_pEventDispatcher->AddEventHandler(id, handler);
	}
	void CoreApi::RemoveEventHandler(EventHandlerID handle)
	{
		m_pEventDispatcher->RemoveEventHandler(handle);
	}
	void CoreApi::Present()
	{
		if(m_pRenderManager)
		{
			m_pRenderManager->Present();
		}
	}
	Allocator* CoreApi::GetAllocator()
	{
		return s_pAllocator;
	}
	ScenePtr CoreApi::GetScene()
	{
		return m_pScene;
	}
	void CoreApi::ResetScene()
	{
		m_pScene->Reset();
	}
	Logger& CoreApi::logger()
	{
		return s_logger;
	}
	bool CoreApi::LoadPackage(const std::string& packageFile)
	{
		return m_pObjectManager->LoadPackage(packageFile);
	}
	void CoreApi::AddCamera(CameraPtr pCamera)
	{
		m_pRenderManager->AddCamera(pCamera);
	}
	void CoreApi::RemoveCamera(CameraPtr pCamera)
	{
		m_pRenderManager->RemoveCamera(pCamera);
	}
	Sys_SoundPtr CoreApi::GetSysSound()
	{
		return m_pSysSound;
	}
	AssetManagerPtr	CoreApi::GetAssetManager()
	{
		return m_pAssetManager;
	}
	TimerManagerPtr	CoreApi::GetTimerManager()
	{
		return m_pTimerManager;
	}
	Sys_TimePtr	CoreApi::GetSysTime()
	{
		return m_pSysTime;
	}
	RUN_MODE CoreApi::GetRunMode()
	{
		return m_runmode;
	}
	DT_CoreApiPtr CoreApi::GetDTCoreApi()
	{
		return m_pDTCore;
	}
	PhysicsManagerPtr CoreApi::GetPhysicsManager()
	{
		return m_pPhysicsManager;
	}
	void CoreApi::QuitApp()
	{
		app_delegate.ExitApp();
	}
	const FrameMetric& CoreApi::GetFrameMetric()
	{
		return m_frameMetric;
	}
	void CoreApi::UpdateFPS()
	{
		static uint64 tick = os_get_tick();

		if(os_get_tick() - tick > 100)
		{
			float avg = m_frameMetric.GetAvgFPS();
			float fps = m_frameMetric.GetFPS();

			std::stringstream str;

			str.precision(3);
			str.setf( std::ios::fixed, std:: ios::floatfield );
			str << "fps: "
				<< fps
				<< ", "
				<< 1000.0f / fps
				<< "ms"
				<< "    avg_fps: "
				<< avg
				<< ", "
				<< 1000.0f / avg
				<< "ms";
			app_delegate.SetWindowTitle(str.str());

			tick = os_get_tick();
		}
	}
	UIManagerPtr CoreApi::GetUIManager()
	{
		return m_pUIManager;
	}
	void* CoreApi::GetMainWndHandle()
	{
		return m_mainWndHandle;
	}
	
}
