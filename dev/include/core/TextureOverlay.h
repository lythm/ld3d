#pragma once

#include "core/OverLay.h"

namespace ld3d
{
	class _DLL_CLASS TextureOverlay : public Overlay
	{
	public:
		TextureOverlay(OverlayPtr pParent = OverlayPtr());
		virtual ~TextureOverlay(void);

		bool											Initialize(RenderManagerPtr pRenderManager, const std::string& name, const math::RectI& rect, TexturePtr pTex);
		void											Release();

		virtual RenderDataPtr							PrepareRenderData();

		void											AttachTexture(TexturePtr pTex);

	private:
		bool											CreateGeometry();
		math::Matrix44 									CreateProjMatrix(const math::RectI& rect);
	private:
		GeometryDataPtr									m_pGeometry;
		RenderDataPtr									m_pRenderData;
		MaterialPtr										m_pMaterial;
		TexturePtr										m_pTexture;
		RenderManagerPtr								m_pRenderManager;
	};
}
