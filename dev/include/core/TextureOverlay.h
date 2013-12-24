#pragma once

#include "core/OverLay.h"

namespace ld3d
{
	class _DLL_CLASS TextureOverlay : public Overlay
	{
	public:
		TextureOverlay(UIManagerPtr pUIManager);
		virtual ~TextureOverlay(void);

		bool											Initialize(RenderManagerPtr pRenderManager, const std::string& name, const math::RectI& rect, TexturePtr pTex);
		void											OnRelease();

		virtual RenderDataPtr							PrepareRenderData();

		void											AttachTexture(TexturePtr pTex, bool auto_release = true);

		TexturePtr										GetTexture();

	private:
		bool											CreateGeometry();

	private:
		GeometryDataPtr									m_pGeometry;
		RenderDataPtr									m_pRenderData;
		MaterialPtr										m_pMaterial;
		TexturePtr										m_pTexture;
		bool											m_texAutoRelease;
		RenderManagerPtr								m_pRenderManager;

		MaterialParameterPtr							m_pParamImage;
		MaterialParameterPtr							m_pParamTrans;
		MaterialParameterPtr							m_pParamScreenSize;
	};
}
