#pragma once



namespace ld3d
{
	class EXPORT_CLASS RenderManager : public std::enable_shared_from_this<RenderManager>
	{
		
		class ScreenQuad
		{
		public:
			
			bool									Init(Sys_Graphics2Ptr pGraphics);
			void									Release();
			void									Render(Sys_Graphics2Ptr pGraphics, Material2Ptr pMaterial);
		private:
			GeometryDataPtr							m_pGeometryData;
		};

		typedef std::shared_ptr<ScreenQuad>			ScreenQuadPtr;
	public:
		RenderManager(void);
		virtual ~RenderManager(void);

		bool										Initialize(Sys_Graphics2Ptr pGraphics, EventDispatcherPtr pED);
		void										Release();
		void										AddRenderData(RenderData2Ptr pData);
		void										AddRenderData(RenderDataPtr pData);
		void										Clear();
		void										Render(const math::Matrix44& view, const math::Matrix44& proj);
		void										Render();
		void										Render(CameraPtr pCamera);
		void										Present();

		void										SetViewMatrix(const math::Matrix44& view);
		void										SetProjMatrix(const math::Matrix44& proj);

		const math::Matrix44&						GetViewMatrix();
		const math::Matrix44&						GetProjMatrix();
		
		Sys_Graphics2Ptr							GetSysGraphics();

		void										SetClearColor(const math::Color4& clr);
		void										SetClearDepth(float d);
		void										SetClearStencil(int s);
		const math::Color4&							GetClearColor();
		void										ResizeFrameBuffer(int cx, int cy);

		void										SetSemanticsValue(RenderData2Ptr pData);

		void										AddLight(LightPtr pLight);
		void										RemoveLight(LightPtr pLight);
		int											GetLightCount();

		RenderTexture2Ptr							GetGBuffer();
		RenderTexture2Ptr							GetABuffer();

		void										DrawFullScreenQuad(Material2Ptr pMaterial);

		const math::Color4&							GetGlobalAmbient();
		void										SetGlobalAmbient(const math::Color4& clr);

		RenderTexture2Ptr							CreateRenderTexture(int c, int w, int h, G_FORMAT format[]);
		void										SetRenderTarget(RenderTarget2Ptr pRT);
		void										ClearRenderTarget(int index, const math::Color4 & clr);
		void										ClearDepthBuffer(CLEAR_DS_FLAG flag, float d, int s);

		int											GetFrameBufferWidth();
		int											GetFrameBufferHeight();

		Material2Ptr								CreateMaterialFromFile(const char* szFile);
		Texture2Ptr									CreateTextureFromFile(const char* szFile);

		void										AddPostEffect(PostEffectPtr pEffect);

		void										AddCamera(CameraPtr pCamera);
		void										RemoveCamera(CameraPtr pCamera);

		GeometryDataPtr								CreateGeometryData();
	private:
		bool										CreateABuffer(int w, int h);
		bool										CreateGBuffer(int w, int h);

		void										DR_G_Pass();
		void										DR_Merge_Pass();
		void										DR_Light_Pass();
		void										RenderPostEffects();
		void										RenderFinal();
		void										RenderForward();
		void										RenderShadowMaps();

		void										DR_DrawRenderData(RenderData2Ptr pData);
		void										FR_DrawRenderData(RenderData2Ptr pData);
		
	private:
		math::Matrix44								m_viewMatrix;
		math::Matrix44								m_projMatrix;

		std::vector<RenderData2Ptr>					m_forwardQueue;
		std::vector<RenderData2Ptr>					m_deferredQueue;
		std::vector<RenderData2Ptr>					m_transparentQueue;
		
		Sys_Graphics2Ptr							m_pGraphics;

		math::Color4								m_clearClr;
		float										m_clearDepth;
		int											m_clearStencil;

		RenderTexture2Ptr							m_pGBuffer;
		RenderTexture2Ptr							m_pABuffer;

		ScreenQuadPtr								m_pScreenQuad;

		LightManagerPtr								m_pLightManager;

		Material2Ptr								m_pLightMaterial;

		Material2Ptr								m_pScreenQuadMaterial;

		math::Color4								m_globalAmbientColor;

		PostEffectManagerPtr						m_pPostEffectManager;

		std::list<CameraPtr>						m_cameras;

		EventDispatcherPtr							m_pEventDispatcher;
	};
}
