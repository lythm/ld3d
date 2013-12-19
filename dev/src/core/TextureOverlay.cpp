#include "core_pch.h"
#include "..\..\include\core\TextureOverlay.h"
#include "core/Material.h"
#include "core/Texture.h"
#include "core/RenderData.h"
#include "core/GeometryData.h"
#include "core/RenderManager.h"
#include "core_utils.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	TextureOverlay::TextureOverlay(OverlayPtr pParent) : Overlay(pParent)
	{
		m_pTexture = nullptr;
	}


	TextureOverlay::~TextureOverlay(void)
	{
	}
	RenderDataPtr TextureOverlay::PrepareRenderData()
	{
		int screen_w = m_pRenderManager->GetFrameBufferWidth();
		int screen_h = m_pRenderManager->GetFrameBufferHeight();

		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("screen_size");
		if(pParam)
		{
			pParam->SetParameterVector(math::Vector2(screen_w, screen_h));
		}
		
		pParam = m_pMaterial->GetParameterByName("overlay_image");
		if(pParam)
		{
			pParam->SetParameterTexture(m_pTexture);
		}

		return m_pRenderData;
	}
	bool TextureOverlay::Initialize(RenderManagerPtr pRenderManager, const std::string& name, const math::RectI& rect, TexturePtr pTex)
	{
		m_pRenderManager				= pRenderManager;
		m_name							= name;
		m_rect							= rect;
		m_pMaterial						= m_pRenderManager->CreateMaterialFromFile("./assets/standard/material/texture_overlay.material");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		if(CreateGeometry() == false)
		{
			return false;
		}
		
		m_pRenderData					= alloc_object<RenderData>();

		m_pRenderData->geometry			= m_pGeometry;
		m_pRenderData->material			= m_pMaterial;

		m_pRenderData->world_matrix.MakeIdentity();

		m_pRenderData->base_vertex		= 0;
		m_pRenderData->index_count		= 0;
		m_pRenderData->start_index		= 0;
		m_pRenderData->vertex_count		= 6;


		AttachTexture(pTex);

		return true;
	}

	bool TextureOverlay::CreateGeometry()
	{
		m_pGeometry						= m_pRenderManager->CreateGeometryData();
		if(m_pGeometry == nullptr)
		{
			return false;
		}

		int x1 = m_rect.left;
		int x2 = m_rect.right;
		int y1 = m_rect.top;
		int y2 = m_rect.bottom;

		struct Vertex
		{
			math::Vector3			pos;
			math::Vector2			uv;
		};
		Vertex verts[] = 
		{
			{math::Vector3(x1, y1, 0),		math::Vector2(0, 0)},
			{math::Vector3(x2, y1, 0),		math::Vector2(1, 0)},
			{math::Vector3(x2, y2, 0),		math::Vector2(1, 1)},
			{math::Vector3(x1, y2, 0),		math::Vector2(0, 1)},
			{math::Vector3(x1, y1, 0),		math::Vector2(0, 0)},
			{math::Vector3(x2, y2, 0),		math::Vector2(1, 1)},
		};

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		layout.AddAttribute(G_FORMAT_R32G32_FLOAT);

		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			m_pGeometry->AllocVertexBuffer(sizeof(Vertex) * 6, verts, false, layout);
		}

		m_pGeometry->EndGeometry();
		return true;
	}
	void TextureOverlay::Release()
	{
		m_pRenderData = nullptr;
		_release_and_reset(m_pGeometry);
		_release_and_reset(m_pMaterial);
		_release_and_reset(m_pTexture);

		Overlay::Release();

	}
	void TextureOverlay::AttachTexture(TexturePtr pTex)
	{
		_release_and_reset(m_pTexture);
		m_pTexture = pTex;
	}
}
