#include "stdafx.h"
#include "GameEngine.h"
#include "AppContext.h"
#include "form_preview.h"
#include "form_scene.h"


GameEngine::GameEngine(void)
{
}


GameEngine::~GameEngine(void)
{
}
bool GameEngine::Initialize()
{
	using namespace ld3d;

	if(AppContext::form_scene == nullptr)
	{
		return false;
	}

	QSize size = AppContext::form_scene->size();
	int w = size.width();
	int h = size.height();

	m_pCore = CoreApiPtr(new CoreApi());

	CoreApi::SetLogger(AppContext::log_info);

	boost::filesystem::path root = AppContext::project_root();


	boost::filesystem::path c = boost::filesystem::current_path();

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
	setting.graphics.wnd = (HWND)AppContext::form_scene->winId();

	setting.input.sysMod = L"";
	setting.input.wnd = (HWND)AppContext::form_scene->winId();

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

#ifdef _WIN64
	m_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/ext_voxel_x64.dll");

#else
	m_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/ext_voxel_x86.dll");
#endif
	
	//m_pCore->GetGameObjectManager()->RegisterComponentClass(dt::DT_GameObjectMonitor::GetClass());
	//m_pCore->GetGameObjectManager()->RegisterComponentClass(dt::DT_VoxelWorldEditor::GetClass());



	m_pCore->GetRenderManager()->SetClearColor(math::Color4(0.3f, 0.2f, 0.4f, 1.0f));
	//m_pCore->GetRenderManager()->SetGlobalAmbient(math::Color4(0, 0, 0, 1.0f));
	return true;
}
void GameEngine::Release()
{
	if(m_pCore != NULL)
	{
		m_pCore->Release();
		m_pCore.reset();
	}
}
ld3d::CoreApiPtr GameEngine::GetCoreApi()
{
	return m_pCore;
}