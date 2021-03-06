#pragma once

//#include "core/ViewFrustum.h"

namespace ld3d
{
	class _DLL_CLASS RenderManager : public std::enable_shared_from_this<RenderManager>
	{
		class ScreenQuad
		{
		public:
			
			bool									Init(Sys_GraphicsPtr pGraphics);
			void									Release();
			void									Render(Sys_GraphicsPtr pGraphics, MaterialPtr pMaterial);
		private:
			GeometryDataPtr							m_pGeometryData;
		};

		typedef std::shared_ptr<ScreenQuad>			ScreenQuadPtr;

	public:
		RenderManager(void);
		virtual ~RenderManager(void);

		bool										Initialize(Sys_GraphicsPtr pGraphics, EventDispatcherPtr pED);
		void										Release();
		void										AddRenderData(RENDER_LAYER layer, RenderDataPtr pData);
		void										Clear();
		void										Render();
		void										Render(CameraPtr pCamera);
		void										Present();

		void										SetViewMatrix(const math::Matrix44& view);
		void										SetProjMatrix(const math::Matrix44& proj);

		const math::Matrix44&						GetViewMatrix();
		const math::Matrix44&						GetProjMatrix();
		
		Sys_GraphicsPtr								GetSysGraphics();

		void										SetClearColor(const math::Color4& clr);
		void										SetClearDepth(float d);
		void										SetClearStencil(int s);
		const math::Color4&							GetClearColor();
		void										OnResizeFramebuffer(int cx, int cy);
		void										ResizeFramebuffer(int cx, int cy, bool fullscreen = false);
		void										AddLight(LightPtr pLight);
		void										RemoveLight(LightPtr pLight);
		int											GetLightCount();

		RenderTexturePtr							GetGBuffer();
		RenderTexturePtr							GetABuffer();

		void										DrawFullScreenQuad(MaterialPtr pMaterial);

		const math::Color4&							GetGlobalAmbient();
		void										SetGlobalAmbient(const math::Color4& clr);

		RenderTexturePtr							CreateRenderTexture(int c, int w, int h, G_FORMAT format[], int lvls = 1);
		RenderTexturePtr							CreateRenderTextureMS(int c, int w, int h, G_FORMAT format[], int samples);
		void										SetRenderTarget(RenderTargetPtr pRT);
		void										ClearRenderTarget(int index, const math::Color4 & clr);
		void										ClearDepthBuffer(CLEAR_DS_FLAG flag, float d, int s);

		int											GetFrameBufferWidth();
		int											GetFrameBufferHeight();

		MaterialPtr									CreateMaterialFromFile(const char* szFile);
		TexturePtr									CreateTextureFromFile(const char* szFile);
		TexturePtr									Create2DTextureArrayFromFileList(const std::vector<std::string>& files);

		void										AddCamera(CameraPtr pCamera);
		void										RemoveCamera(CameraPtr pCamera);

		GeometryDataPtr								CreateGeometryData();

		void										SetMatrixBlock(MaterialPtr pMaterial, const math::Matrix44& world);
		void										SetDRBuffer(MaterialPtr pMaterial);
		void										SetABuffer(MaterialPtr pMaterial);
		void										SetGBuffer(MaterialPtr pMaterial);

		DepthStencilBufferPtr						GetDepthStencilBuffer();

		void										DrawRenderData(RenderDataPtr pData, MaterialPtr pMaterial = nullptr);

		void										DrawShadowMapGeometry(const math::Matrix44& view, const math::Matrix44& proj);

		void										EmitViewFrustumCullEvent(const math::ViewFrustum& vf);

		void										SetViewport(const math::RectI& vp);

		bool										IsFullscreen();

		LightManagerPtr								GetLightManager();

		RenderParametersPtr							GetRenderParams() const;
		// test
		void										RenderTest(CameraPtr pCamera);
		//
	private:
		
		void										RenderBackground(RenderTargetPtr pTarget);
		void										RenderOverlay();
		void										RenderShadowMaps(CameraPtr pCamera);

		void										Draw_Texture(TexturePtr pTex);
	private:
		
		RenderQueuePtr								m_pRenderQueue;

		Sys_GraphicsPtr								m_pGraphics;

		DepthStencilBufferPtr						m_pDSBuffer;

		ScreenQuadPtr								m_pScreenQuad;

		LightManagerPtr								m_pLightManager;

		MaterialPtr									m_pLightMaterial;

		std::list<CameraPtr>						m_cameras;

		EventDispatcherPtr							m_pEventDispatcher;

		MaterialPtr									m_pDrawTextureMaterial;

		MaterialPtr									m_pShadowMapMaterial;

		RenderParametersPtr							m_pRenderParams;
		RenderSystem_DeferredPtr					m_pDR;
		RenderSystem_ForwardPtr						m_pFR;
		RenderSystem_PostPtr						m_pPR;
	};
}
