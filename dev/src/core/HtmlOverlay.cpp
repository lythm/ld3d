#include "core_pch.h"
#include "..\..\include\core\HtmlOverlay.h"
#include "core_utils.h"
#include "core/TextureOverlay.h"
#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"
#include "core/Texture.h"
#include "core/WebpageRenderer.h"

namespace ld3d
{
	HtmlOverlay::HtmlOverlay(UIManagerPtr pUIManager) : Overlay(pUIManager)
	{
	}


	HtmlOverlay::~HtmlOverlay(void)
	{
	}
	void HtmlOverlay::OnRelease()
	{
		_release_and_reset(m_pPageRenderer);
		_release_and_reset(m_pTexture);

	}
	bool HtmlOverlay::Initialize(RenderManagerPtr pRenderManager, WebpageRendererPtr pRenderer, const std::string& name, const math::RectI& rect)
	{
		if(pRenderer == nullptr)
		{
			return false;
		}

		m_pRenderManager				= pRenderManager;
		m_name							= name;
		m_rect							= rect;

		m_pTexOverlay = alloc_object<TextureOverlay>(m_pUIManager);
		if(false == m_pTexOverlay->Initialize(m_pRenderManager, name + "_internal_", math::RectI(0, 0, rect.width(), rect.height()), TexturePtr()))
		{
			return false;
		}

		m_pTexOverlay->LinkTo(shared_from_this());
	
		if(false == ResizeTexture(m_rect.width(), m_rect.height()))
		{
			return false;
		}

		m_pPageRenderer = pRenderer;

		m_pPageRenderer->SetRenderTarget(m_pTexture);

		int x = 0;
		int y = 0;
		GetScreenCoord(x, y);
		m_pPageRenderer->SetScreenCoord(x, y);
		return true;
	}
	bool HtmlOverlay::ResizeTexture(uint32 w, uint32 h)
	{
		_release_and_reset(m_pTexture);

		m_pTexture = m_pRenderManager->GetSysGraphics()->CreateTexture2D(G_FORMAT_R8G8B8A8_UNORM, w, h, 1, true);
		if(m_pTexture == nullptr)
		{
			return false;
		}

		m_pTexOverlay->AttachTexture(m_pTexture, false);
		return true;
	}
	RenderDataPtr HtmlOverlay::PrepareRenderData()
	{
		int x = 0;
		int y = 0;
		GetScreenCoord(x, y);
		m_pPageRenderer->SetScreenCoord(x, y);

		return RenderDataPtr();
	}
	void HtmlOverlay::OnResize(uint32 w, uint32 h)
	{
		ResizeTexture(w, h);
		m_pTexOverlay->Resize(w, h);
	}
	void HtmlOverlay::Show(bool show)
	{
		Overlay::Show(show);
		if(m_pPageRenderer)
		{
			m_pPageRenderer->SetVisible(show);
		}
	}
	void HtmlOverlay::LoadPage(const std::string& url)
	{
		m_pPageRenderer->LoadPage(url);
	}
	WebpageRendererPtr HtmlOverlay::GetWebpageRenderer()
	{
		return m_pPageRenderer;
	}
}
