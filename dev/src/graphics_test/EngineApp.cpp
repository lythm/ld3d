#include "stdafx.h"
#include "EngineApp.h"
#include <tchar.h>



namespace ld3d
{
	void _log(const std::wstring& str)
	{
		OutputDebugString(str.c_str());
	}
	EngineApp::EngineApp(void)
	{
	}


	EngineApp::~EngineApp(void)
	{
	}
	void EngineApp::OnUpdate()
	{
		m_pGraphics->ClearRenderTarget(0, math::Color4(0.3, 0.5, 0.7, 1));
		m_pGraphics->ClearDepthStencil(CLEAR_ALL, 1.0f, 0);

		m_pGraphics->SetShaderProgram(m_pProgram);
		
		
		//m_pGraphics->Draw(PT_TRIANGLE_LIST, 3, 0);
		m_pGraphics->DrawIndexed(m_pGeometry, 3, 0, 0);

		m_pGraphics->Present();

		ShowFPS();
	}
	bool EngineApp::OnInit()
	{
		using namespace ld3d;

		if(false == m_mod.load_sys(L"./ogl4graphics_x64.dll"))
		{
			return false;
		}

		m_pGraphics = m_mod.pSys;
		
		GraphicsSetting setting;
		setting.sysMod = L"./ogl4graphics_x64.dll";
		setting.backBufferCount = 2;
		setting.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
		setting.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
		setting.frameBufferHeight = GetClientHeight();
		setting.frameBufferWidth = GetClientWidth();
		setting.multiSampleCount = 1;
		setting.multiSampleQuality = 0;
		setting.windowed = true;
		setting.wnd = GetWnd();

		
		if(false == m_pGraphics->Initialize(setting))
		{
			return false;
		}

		
		math::Vector3 verts[] = 
		{
			math::Vector3(0, 0, 1),
			math::Vector3(0, 1, 1),
			math::Vector3(1, 0, 1),
		};

		unsigned short indices[] = 
		{
			0, 1, 2,
		};
		GPUBufferPtr pVB = m_pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * 3, nullptr, false);

		void* data = pVB->Map(MAP_DEFAULT);
		memcpy(data, verts, sizeof(math::Vector3) * 3);
		pVB->Unmap();


		GPUBufferPtr pIB = m_pGraphics->CreateBuffer(BT_INDEX_BUFFER, sizeof(short) * 3, nullptr, false);

		data = pIB->Map(MAP_DEFAULT);
		memcpy(data, indices, sizeof(short) * 3);
		pIB->Unmap();

		VertexLayout layout;

		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);		// position
		
		
		m_pGeometry = m_pGraphics->CreateGeometryData();

		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			m_pGeometry->AttachIndexBuffer(pIB, G_FORMAT_R16_UINT);
			m_pGeometry->AttachVertexBuffer(pVB, layout);
		}
		m_pGeometry->EndGeometry();


		m_pProgram = m_pGraphics->CreateShaderProgram();

		m_pProgram->AttachShaderFromFile(ST_VERTEX_SHADER, "./assets/standard/material/1.glsl");
		m_pProgram->AttachShaderFromFile(ST_PIXEL_SHADER, "./assets/standard/material/2.glsl");

		m_pProgram->Link();

		m_pProgram->Validate();

		return true;
	}
	void EngineApp::OnRelease()
	{
		m_pGeometry->Release();


		m_pGraphics->Release();
		m_pGraphics.reset();
	}

	void EngineApp::ShowFPS()
	{
		static int tick = GetTickCount();

		static int frames = 0;
		int dt = GetTickCount() - tick;

		int iv = 100;
		if(dt >= iv)
		{

			wchar_t buffer[100];

			float fps = float(frames * 1000) / float(dt);
			swprintf(buffer, 100, L"fps : %.3f - %fms", fps, 1000.0f / fps);

			SetTitle(buffer);

			tick = GetTickCount();
			frames = 0;
		}

		frames ++;
	}

	void EngineApp::HandleMessage(MSG& msg)
	{
	}
}






int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	using namespace ld3d;
	EngineApp app;

	if(false == app.Initialize(hInstance, L"Main Window", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
