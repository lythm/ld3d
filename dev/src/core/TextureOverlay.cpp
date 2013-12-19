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
	}


	TextureOverlay::~TextureOverlay(void)
	{
	}
	RenderDataPtr TextureOverlay::PrepareRenderData()
	{
		return m_pRenderData;
	}
	bool TextureOverlay::Initialize(RenderManagerPtr pRenderManager, const std::string& name, const math::RectI& rect, TexturePtr pTex)
	{
		m_pRenderManager				= pRenderManager;
		m_name							= name;
		m_rect							= rect;
		m_pTexture						= pTex;
		m_pMaterial						= m_pRenderManager->CreateMaterialFromFile("./assets/standard/material/texture_overlay.material");
		if(m_pMaterial == nullptr)
		{
			return false;
		}

		m_pGeometry						= m_pRenderManager->CreateGeometryData();
		if(m_pGeometry == nullptr)
		{
			return false;
		}

		math::Vector3 verts[] = 
		{
			math::Vector3(-1, 1, 0),
			math::Vector3(1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, -1, 0),
		};

		VertexLayout layout;
		layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		m_pGeometry->BeginGeometry(PT_TRIANGLE_LIST);
		{
			m_pGeometry->AllocVertexBuffer(sizeof(math::Vector3) * 6, verts, false, layout);
		}
		m_pGeometry->EndGeometry();


		m_pRenderData					= alloc_object<RenderData>();

		m_pRenderData->geometry			= m_pGeometry;
		m_pRenderData->material			= m_pMaterial;

		m_pRenderData->world_matrix.MakeIdentity();

		m_pRenderData->base_vertex		= 0;
		m_pRenderData->index_count		= 0;
		m_pRenderData->start_index		= 0;
		m_pRenderData->vertex_count		= 6;


		AttachTexture(m_pTexture);
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
		MaterialParameterPtr pParam = m_pMaterial->GetParameterByName("overlay_image");
		if(pParam)
		{
			//pParam->SetParameterTexture(pTex);
		}
		_release_and_reset(m_pTexture);

		m_pTexture = pTex;
	}
}
