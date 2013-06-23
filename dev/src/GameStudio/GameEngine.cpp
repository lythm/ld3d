#include "stdafx.h"
#include "GameEngine.h"
#include "AppContext.h"
#include "form_preview.h"
#include "form_scene.h"
#include "GridMesh.h"


GameEngine::GameEngine(void)
{
	m_bShowGrid = true;
}


GameEngine::~GameEngine(void)
{
}
bool GameEngine::Initialize(QWidget* pTarget)
{
	using namespace ld3d;
	using namespace math;

	QSize size = pTarget->size();
	int w = size.width();
	int h = size.height();

	m_pCore = CoreApiPtr(new CoreApi());

	CoreApi::SetLogger(AppContext::log_info);

#ifdef _WIN64
	SysSetting setting;
	setting.graphics.sysMod = L"./d11graphics_x64.dll";
	setting.graphics.backBufferCount = 2;
	setting.graphics.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
	setting.graphics.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
	setting.graphics.frameBufferHeight = h;
	setting.graphics.frameBufferWidth = w;
	setting.graphics.multiSampleCount = 1;
	setting.graphics.multiSampleQuality = 0;
	setting.graphics.windowed = true;
	setting.graphics.wnd = (void*)pTarget->winId();

	setting.input.sysMod = L"";
	setting.input.wnd = (void*)pTarget->winId();

	setting.sound.maxChannels = 100;
	setting.sound.sysMod = L"./fmod_sound_x64.dll";

	setting.physics.sysMod = L"";

	setting.network.sysMod = L"./network_x64.dll";

#else
	SysSetting setting;
	setting.graphics.sysMod = L"./d11graphics_x86.dll";
	setting.graphics.backBufferCount = 2;
	setting.graphics.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
	setting.graphics.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
	setting.graphics.frameBufferHeight = h;
	setting.graphics.frameBufferWidth = w;
	setting.graphics.multiSampleCount = 1;
	setting.graphics.multiSampleQuality = 0;
	setting.graphics.windowed = true;
	setting.graphics.wnd = pWnd->m_hWnd;

	setting.input.sysMod = L"";
	setting.input.wnd = pWnd->m_hWnd;

	setting.sound.maxChannels = 100;
	setting.sound.sysMod = L"./fmod_sound_x86.dll";

	setting.physics.sysMod = L"";

	setting.network.sysMod = L"./network_x86.dll";
#endif
	if(false == m_pCore->Initialize(setting, &g_Allocator))
	{
		return false;
	}


	m_pRenderManager = m_pCore->GetRenderManager();


#ifdef _WIN64
	m_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/ext_voxel_x64.dll");

#else
	m_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/ext_voxel_x86.dll");
#endif
	
	m_pRenderManager->SetClearColor(math::Color4(0.3f, 0.2f, 0.4f, 1.0f));
	//m_pRenderManager->SetGlobalAmbient(math::Color4(0, 0, 0, 1.0f));

	

	m_pGrid = alloc_shared<GridMesh>();

	if(false == m_pGrid->Init(m_pCore, 1000, 10))
	{
		return false;
	}
	
	return true;
}
void GameEngine::Release()
{
	if(m_pGrid)
	{
		m_pGrid->Release();
		m_pGrid.reset();
	}
	
	if(m_pCore != nullptr)
	{
		m_pCore->Release();
		m_pCore.reset();
	}
}
ld3d::CoreApiPtr GameEngine::GetCoreApi()
{
	return m_pCore;
}

void GameEngine::Update()
{
	m_pCore->Update();
}
void GameEngine::Render()
{
	m_bShowGrid ? m_pCore->AddRenderData(m_pGrid) : 0;

	m_pCore->Render();
	m_pCore->Present();
	m_pCore->ClearRenderQueue();
}
void GameEngine::Render(ld3d::CameraPtr pCamera)
{
	m_bShowGrid ? m_pCore->AddRenderData(m_pGrid) : 0;

	m_pCore->Render(pCamera);
	m_pCore->Present();
	m_pCore->ClearRenderQueue();
}
void GameEngine::Resize(int w, int h)
{
	m_pCore->GetRenderManager()->ResizeFrameBuffer(w, h);
	m_pCore->GetSysGraphics()->SetViewPort(0, 0, w, h);
}
void GameEngine::ShowGrid(bool bShow)
{
	m_bShowGrid = bShow;
}
bool GameEngine::GridVisible()
{
	return m_bShowGrid;
}
ld3d::GameObjectPtr	GameEngine::RootObject()
{
	return m_pCore ? m_pCore->Root() : nullptr;
}