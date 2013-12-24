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
	TextureOverlay::TextureOverlay(UIManagerPtr pUIManager) : Overlay(pUIManager)
	{
		m_pTexture					= nullptr;
		m_texAutoRelease			= true;
	}


	TextureOverlay::~TextureOverlay(void)
	{
	}
	RenderDataPtr TextureOverlay::PrepareRenderData()
	{
		float screen_w = (float)m_pRenderManager->GetFrameBufferWidth();
		float screen_h = (float)m_pRenderManager->GetFrameBufferHeight();

		if(m_pParamScreenSize)
		{
			m_pParamScreenSize->SetParameterVector(math::Vector2(screen_w, screen_h));
		}
		
		m_pParamImage = m_pMaterial->GetParameterByName("overlay_image");
		if(m_pParamImage)
		{
			m_pParamImage->SetParameterTexture(m_pTexture);
		}

		math::Matrix44 trans;
		trans.MakeIdentity();
		trans.SetScale(math::Vector3(m_rect.width(), m_rect.height(), 1));

		int x = 0;
		int y = 0;
		GetScreenCoord(x, y);
		trans.SetTranslation(math::Vector3((float)x, (float)y, 0));

		m_pParamTrans = m_pMaterial->GetParameterByName("trans");
		if(m_pParamTrans)
		{
			m_pParamTrans->SetParameterMatrix(trans);
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


		m_pParamImage					= m_pMaterial->GetParameterByName("overlay_image");;
		m_pParamTrans					= m_pMaterial->GetParameterByName("trans");;
		m_pParamScreenSize				= m_pMaterial->GetParameterByName("screen_size");;


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

		struct Vertex
		{
			math::Vector3			pos;
			math::Vector2			uv;
		};
		Vertex verts[] = 
		{
			{math::Vector3(0, 0, 0),		math::Vector2(0, 0)},
			{math::Vector3(1, 0, 0),		math::Vector2(1, 0)},
			{math::Vector3(1, 1, 0),		math::Vector2(1, 1)},
			{math::Vector3(0, 1, 0),		math::Vector2(0, 1)},
			{math::Vector3(0, 0, 0),		math::Vector2(0, 0)},
			{math::Vector3(1, 1, 0),		math::Vector2(1, 1)},
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
	void TextureOverlay::OnRelease()
	{
		m_pRenderData = nullptr;
		_release_and_reset(m_pGeometry);
		_release_and_reset(m_pMaterial);
		if(m_texAutoRelease)
		{
			_release_and_reset(m_pTexture);
		}
	}
	void TextureOverlay::AttachTexture(TexturePtr pTex, bool auto_release)
	{
		if(m_texAutoRelease)
		{
			_release_and_reset(m_pTexture);
		}
		m_pTexture = pTex;
		m_texAutoRelease = auto_release;
	}
	TexturePtr TextureOverlay::GetTexture()
	{
		return m_pTexture;
	}
}
