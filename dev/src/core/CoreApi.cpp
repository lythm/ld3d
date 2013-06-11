#include "core_pch.h"
#include "..\..\include\core\CoreApi.h"

#include "core\SysManager.h"
#include "core\Sys_Graphics.h"
#include "core\Sys_Network.h"
#include "core\GameObjectManager.h"
#include "core\RenderManager.h"
#include "core\AssetsManager.h"
#include "core\TimerManager.h"


#include "core\Event.h"
#include "core\PoolAllocator.h"
#include "core\StdAllocator.h"
#include "core\Scene.h"

#include "core\GameObject.h"

#include "WMInput.h"
#include "core\Sys_Sound.h"


#include "Time64.h"


namespace ld3d
{
	Allocator*										CoreApi::s_pAllocator;
	CoreApi::Logger									CoreApi::s_logger;
	static StdAllocator								g_stdAllocator;

	CoreApi::CoreApi(void)
	{
		m_runmode					= RM_RT;
	}


	CoreApi::~CoreApi(void)
	{
	}
	void CoreApi::Update()
	{
		m_pSysTime->Update();

		float dt = m_pSysTime->Second() - m_lastFrameTime;
		m_lastFrameTime = m_pSysTime->Second();

		s_pAllocator->Update();
		m_pTimerManager->Update();

		m_pSysNetwork->Update();
		m_pSysInput->Update();
		m_pSysSound->Update();
		m_pScene->Update(dt);
		
	}
	bool CoreApi::Initialize(const SysSetting& setting, Allocator* pAlloc, DT_CoreApiPtr pDTCore)
	{
		m_pDTCore = pDTCore;
		m_runmode = m_pDTCore == nullptr ? RM_RT : RM_DT;
		s_pAllocator = pAlloc;

		if(s_pAllocator == nullptr)
		{
			s_pAllocator = &g_stdAllocator;
		}
		m_pSysTime = s_pAllocator->AllocObject<Time64>();
		m_pSysTime->Start();
		m_pEventDispatcher = s_pAllocator->AllocObject<EventDispatcher>();
		m_pSysManager = s_pAllocator->AllocObject<SysManager>();
		m_pSysGraphics = m_pSysManager->LoadSysGraphics(setting.graphics.sysMod.c_str());
		
		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(setting.graphics))
		{
			return false;
		}

		m_pSysInput = s_pAllocator->AllocObject<WMInput>();

		if(false == m_pSysInput->Initialize(setting.input.wnd))
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
		m_pTimerManager = s_pAllocator->AllocObject<TimerManager>();

		if(m_pTimerManager->Init(m_pSysTime) == false)
		{
			return false;
		}

		m_pAssetManager = s_pAllocator->AllocObject<AssetManager>();
		if(m_pAssetManager->Initialize(m_pSysGraphics, m_pSysSound) == false)
		{
			return false;
		}

		m_pRenderManager = s_pAllocator->AllocObject<RenderManager>();
		if(m_pRenderManager->Initialize(m_pSysGraphics, m_pEventDispatcher) == false)
		{
			return false;
		}
		

		

		m_pObjectManager = s_pAllocator->AllocObject<GameObjectManager>();
		if(m_pObjectManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pScene = s_pAllocator->AllocObject<Scene, GameObjectManagerPtr>(m_pObjectManager);



		
		m_lastFrameTime = m_pSysTime->Second();
		return true;
	}
	void CoreApi::Release()
	{
		if(m_pScene)
		{
			m_pScene->Release();
			m_pScene.reset();
		}
		if(m_pObjectManager)
		{
			m_pObjectManager->Release();
			m_pObjectManager.reset();
		}
		
		if(m_pRenderManager)
		{
			m_pRenderManager->Release();
			m_pRenderManager.reset();
		}

		if(m_pAssetManager)
		{
			m_pAssetManager->Release();
			m_pAssetManager.reset();
		}
		if(m_pTimerManager)
		{
			m_pTimerManager->Release();
			m_pTimerManager.reset();
		}

		if(m_pSysNetwork)
		{
			m_pSysNetwork->Release();
			m_pSysNetwork.reset();
		}

		if(m_pSysInput)
		{
			m_pSysInput->Release();
			m_pSysInput.reset();
		}
		if(m_pSysGraphics)
		{
			m_pSysGraphics->Release();
			m_pSysGraphics.reset();
		}
		if(m_pSysSound)
		{
			m_pSysSound->Release();
			m_pSysSound.reset();
		}

		m_pSysManager.reset();

		if(m_pEventDispatcher)
		{
			m_pEventDispatcher->Clear();
			m_pEventDispatcher.reset();
		}

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
	void CoreApi::HandleMessage(MSG& msg)
	{
		boost::shared_ptr<Event_WindowMessage> pEvent = s_pAllocator->AllocObject<Event_WindowMessage, MSG>(msg);
		pEvent->msg = msg;

		DispatchEvent(pEvent);

		if(m_pSysInput)
		{
			m_pSysInput->HandleMessage(msg);
		}
	}
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
	void CoreApi::AddRenderData(RenderDataPtr pData)
	{
		if(m_pRenderManager)
		{
			m_pRenderManager->AddRenderData(pData);
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
	GameObjectPtr CoreApi::CreateGameObject(const std::wstring& name)
	{
		GameObjectPtr pObj = m_pObjectManager->CreateGameObject(name);
		pObj->LinkTo(m_pScene->Root());

		return pObj;
	}
	GameObjectPtr CoreApi::CreatGameObjectFromTemplate(const std::wstring& tpl, const std::wstring& name)
	{
		GameObjectPtr pObj = m_pObjectManager->CreateObjectFromTemplate(tpl);

		if(pObj == nullptr)
		{
			return GameObjectPtr();
		}
		if(name != L"")
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
	GameObjectComponentPtr CoreApi::CreateGameObjectComponent(const std::wstring& name)
	{
		return m_pObjectManager->CreateComponent(name);
	}
	void CoreApi::DispatchEvent(EventPtr pEvent)
	{
		m_pEventDispatcher->DispatchEvent(pEvent);
	}
	EventDispatcher::EventHandlerHandle CoreApi::AddEventHandler(uint32 id, EventDispatcher::EventHandler handler)
	{
		return m_pEventDispatcher->AddEventHandler(id, handler);
	}
	void CoreApi::RemoveEventHandler(EventDispatcher::EventHandlerHandle handle)
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
	void CoreApi::Log(const std::wstring& text)
	{
		if(s_logger.empty() == false)
		{
			s_logger(text);
		}

#ifdef _DEBUG
		OutputDebugString(text.c_str());
		OutputDebugString(L"\r\n");
#endif
	}
	void CoreApi::SetLogger(Logger logger)
	{
		s_logger = logger;
	}
	bool CoreApi::LoadPackage(const std::wstring& packageFile)
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
}
