#pragma once

#include "core/OverLay.h"

namespace ld3d
{
	class _DLL_CLASS HtmlOverlay : public Overlay
	{
	public:
		HtmlOverlay(UIManagerPtr pUIManager);
		virtual ~HtmlOverlay(void);

		void									OnRelease();
		bool									Initialize(RenderManagerPtr pRenderManager, WebpageRendererPtr pRenderer, const std::string& name, const math::RectI& rect);

		RenderDataPtr							PrepareRenderData();

		void									OnResize(uint32 w, uint32 h);

	private:
		bool									ResizeTexture(uint32 w, uint32 h);
		bool									_handle_input(EventPtr pEvent);
	private:
		TextureOverlayPtr						m_pTexOverlay;
		TexturePtr								m_pTexture;
		RenderManagerPtr						m_pRenderManager;
		WebpageRendererPtr						m_pPageRenderer;
	};

}