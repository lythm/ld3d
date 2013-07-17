#include "stdafx.h"
#include "EngineApp.h"
#include <tchar.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_major_storage.hpp>
#include <glm/gtc/quaternion.hpp>

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

		math::Matrix44 view;
		math::Matrix44 proj;
		math::Matrix44 t;
		math::Vector3 eye(20, 20, 20);
		
		static float radius = 0;
		radius += 0.001;

		t = math::MatrixRotationAxisY(radius);
		//math::TransformCoord(eye, t);

		view = math::MatrixLookAtLH(eye, math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
		proj = math::MatrixPerspectiveFovLH(0.25 * 3.14, 4.0 / 3.0, 0.01, 10000);
		
		ShaderProgram::ParameterID param = m_pProgram->FindParameterByName("v");
		m_pProgram->SetParameterMatrix(param, view);


		param = m_pProgram->FindParameterByName("p");
		m_pProgram->SetParameterMatrix(param, proj);
		
		param = m_pProgram->FindParameterByName("base");
		m_pProgram->SetParameterTexture(param, m_pTex);

		
		m_pGraphics->SetRenderTarget(m_pRenderTarget);

		m_pGraphics->ClearRenderTarget(0, math::Color4(0, 0, 0.7, 1));
		m_pGraphics->ClearDepthStencil(CLEAR_ALL, 1.0f, 0);

		m_pGraphics->SetShaderProgram(m_pProgram);


		m_pGraphics->DrawIndexed(m_pGeometry, 36, 0, 0);



		param = m_pProgram->FindParameterByName("base");
		//m_pProgram->SetParameterTexture(param, m_pRenderTarget->GetTexture(0));

		m_pGraphics->SetRenderState(m_pRenderState);

		m_pGraphics->SetRenderTarget(RenderTarget2Ptr());

		m_pGraphics->ClearRenderTarget(0, math::Color4(0.3, 0.5, 0.7, 1));
		m_pGraphics->ClearDepthStencil(CLEAR_ALL, 1.0f, 0);

		m_pGraphics->SetShaderProgram(m_pProgram);
		m_pGraphics->DrawIndexed(m_pGeometry, 36, 0, 0);
		
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

		
		m_pGeometry = CreateCube(10);

		m_pProgram = m_pGraphics->CreateShaderProgram();

		m_pProgram->AttachShaderFromFile(ST_VERTEX_SHADER, "./assets/standard/material/1.glsl");
		m_pProgram->AttachShaderFromFile(ST_PIXEL_SHADER, "./assets/standard/material/2.glsl");

		m_pProgram->Link();

		m_pProgram->Validate();

		
		/*uint32* initData = new uint32[1024 * 1024];

		memset(initData, 255, 1024 * 1024 * sizeof(uint32));

		m_pTex = m_pGraphics->CreateTexture2D(G_FORMAT_R8G8B8A8_UNORM, 1024 , 1024);

		void* data = m_pTex->Map();


		memcpy(data, initData, 1024 * 1024 * sizeof(uint32));

		m_pTex->UnMap();*/
		
		m_pTex = m_pGraphics->CreateTextureFromFile("./assets/standard/texture/15.png", false);
		

		m_pSampler = m_pGraphics->CreateSampler();


		m_pSampler->SetAddressMode(SamplerState::AM_CLAMP, SamplerState::AM_CLAMP, SamplerState::AM_CLAMP);
		m_pSampler->SetFilter(SamplerState::FILTER_ANISOTROPIC);

		m_pTex->SetSampler(m_pSampler);

		ShaderProgram::ParameterID param = m_pProgram->FindParameterByName("base");
		m_pProgram->SetParameterTexture(param, m_pTex);


		DepthStencilBufferPtr pDS = m_pGraphics->CreateDepthStencilBuffer(G_FORMAT_D32_FLOAT, 800, 600);
		Texture2Ptr pTex = m_pGraphics->CreateTexture2D(G_FORMAT_R8G8B8A8_UNORM, 800, 600, 1, false);
		pTex->SetSampler(m_pSampler);

		m_pRenderTarget = m_pGraphics->CreateRenderTexture();

		m_pRenderTarget->AddTexture(pTex);
		m_pRenderTarget->SetDepthStencilBuffer(pDS);

		m_pRenderState = m_pGraphics->CreateRenderState();

		m_pRenderState->Begin();
		m_pRenderState->SetCullMode(RS_CULL_BACK);
		m_pRenderState->SetFrontCounterClockwise(false);
		m_pRenderState->End();
		//Sleep(1000);


		material_script::Compiler cl;

		Material2Ptr pMat = cl.CompileFromFile("./assets/standard/material/1.material");


		return true;
	}
	void EngineApp::OnRelease()
	{
		m_pSampler->Release();
		m_pSampler.reset();

		m_pTex->Release();
		m_pTex.reset();

		m_pGeometry->Release();
		m_pGeometry.reset();


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
	GeometryDataPtr EngineApp::CreateCube(float size)
	{
		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
			math::Vector2 uv;
			
		};

		size = size / 2.0f;
		Vertex pVerts[] = 
		{
			// front
			{math::Vector3(-size, size, -size), math::Vector3(0, 0, -1), math::Vector2(0, 0), },
			{math::Vector3(size, size, -size), math::Vector3(0, 0, -1), math::Vector2(1, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(0, 0, -1), math::Vector2(1, 1),},
			{math::Vector3(-size, -size, -size), math::Vector3(0, 0, -1), math::Vector2(0, 1),},

			// back
			{math::Vector3(-size, size, size), math::Vector3(0, 0, 1), math::Vector2(0, 0),},
			{math::Vector3(size, size, size), math::Vector3(0, 0, 1), math::Vector2(1, 0),},
			{math::Vector3(size, -size, size), math::Vector3(0, 0, 1), math::Vector2(1, 1),},
			{math::Vector3(-size, -size, size), math::Vector3(0, 0, 1), math::Vector2(0, 1),},

			// top
			{math::Vector3(-size, size, size), math::Vector3(0, 1, 0), math::Vector2(0, 0),},
			{math::Vector3(size, size, size), math::Vector3(0, 1, 0), math::Vector2(1, 0),},
			{math::Vector3(size, size, -size), math::Vector3(0, 1, 0), math::Vector2(1, 1),},
			{math::Vector3(-size, size, -size), math::Vector3(0, 1, 0), math::Vector2(0, 1),},
			// bottom
			{math::Vector3(-size, -size, size), math::Vector3(0, -1, 0), math::Vector2(0, 0),},
			{math::Vector3(size, -size, size), math::Vector3(0, -1, 0), math::Vector2(1, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(0, -1, 0), math::Vector2(1, 1),},
			{math::Vector3(-size, -size, -size), math::Vector3(0, -1, 0), math::Vector2(0, 1),},

			// left
			{math::Vector3(-size, size, size), math::Vector3(-1, 0, 0), math::Vector2(0, 0),},
			{math::Vector3(-size, size, -size), math::Vector3(-1, 0, 0), math::Vector2(1, 0),},
			{math::Vector3(-size, -size, -size), math::Vector3(-1, 0, 0), math::Vector2(1, 1),},
			{math::Vector3(-size, -size, size), math::Vector3(-1, 0, 0), math::Vector2(0, 1),},
			// right
			{math::Vector3(size, size, size), math::Vector3(1, 0, 0), math::Vector2(0, 0),},
			{math::Vector3(size, size, -size), math::Vector3(1, 0, 0), math::Vector2(1, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(1, 0, 0), math::Vector2(1, 1),},
			{math::Vector3(size, -size, size), math::Vector3(1, 0, 0), math::Vector2(0, 1),},
		};

		uint32 pIndice[] = 
		{
			// front
			0, 1, 2,
			0, 2, 3,

			// back
			4, 6, 5, 
			4, 7, 6,


			//top
			8, 9, 10,
			8, 10, 11,

			// bottom
			12, 14, 13,
			12, 15, 14,

			// left
			16, 17, 18,
			16, 18, 19,

			// right
			20, 22, 21,
			20, 23, 22,

		};

		GeometryDataPtr pGeom = m_pGraphics->CreateGeometryData();

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32_FLOAT);

		pGeom->BeginGeometry(PT_TRIANGLE_LIST);
		{
			pGeom->AllocIndexBuffer(sizeof(uint32) * 36, pIndice, false, G_FORMAT_R32_UINT);
			pGeom->AllocVertexBuffer(sizeof(Vertex) * 24, pVerts, false, layout);
		}
		pGeom->EndGeometry();

		return pGeom;
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
