#pragma once



namespace ld3d
{
	class EXPORT_CLASS RenderManager : public std::enable_shared_from_this<RenderManager>
	{
		struct MATRIX_BLOCK
		{
			math::Matrix44							MATRIX_WORLD;
			math::Matrix44							MATRIX_VIEW;
			math::Matrix44							MATRIX_PROJ;

			math::Matrix44							MATRIX_I_WORLD;
			math::Matrix44							MATRIX_I_VIEW;
			math::Matrix44							MATRIX_I_PROJ;

			math::Matrix44							MATRIX_WV;
			math::Matrix44							MATRIX_WVP;
			
			math::Matrix44							MATRIX_I_WV;
			math::Matrix44							MATRIX_I_WVP;
			math::Matrix44							MATRIX_I_VP;
		};
		
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
		
		Sys_GraphicsPtr								GetSysGraphics();

		void										SetClearColor(const math::Color4& clr);
		void										SetClearDepth(float d);
		void										SetClearStencil(int s);
		const math::Color4&							GetClearColor();
		void										OnResizeRenderWindow(int cx, int cy);

		void										AddLight(LightPtr pLight);
		void										RemoveLight(LightPtr pLight);
		int											GetLightCount();

		RenderTexturePtr							GetGBuffer();
		RenderTexturePtr							GetABuffer();

		void										DrawFullScreenQuad(MaterialPtr pMaterial);

		const math::Color4&							GetGlobalAmbient();
		void										SetGlobalAmbient(const math::Color4& clr);

		RenderTexturePtr							CreateRenderTexture(int c, int w, int h, G_FORMAT format[]);
		void										SetRenderTarget(RenderTargetPtr pRT);
		void										ClearRenderTarget(int index, const math::Color4 & clr);
		void										ClearDepthBuffer(CLEAR_DS_FLAG flag, float d, int s);

		int											GetFrameBufferWidth();
		int											GetFrameBufferHeight();

		MaterialPtr									CreateMaterialFromFile(const char* szFile);
		TexturePtr									CreateTextureFromFile(const char* szFile);

		void										AddPostEffect(PostEffectPtr pEffect);

		void										AddCamera(CameraPtr pCamera);
		void										RemoveCamera(CameraPtr pCamera);

		GeometryDataPtr								CreateGeometryData();

		void										UpdateMatrixBlock(MaterialPtr pMaterial, const math::Matrix44& world);
		void										UpdateDRBuffer(MaterialPtr pMaterial);
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

		void										DR_DrawRenderData(RenderDataPtr pData);
		void										FR_DrawRenderData(RenderDataPtr pData);
		
	private:
		math::Matrix44								m_viewMatrix;
		math::Matrix44								m_projMatrix;

		std::vector<RenderDataPtr>					m_forwardQueue;
		std::vector<RenderDataPtr>					m_deferredQueue;
		std::vector<RenderDataPtr>					m_transparentQueue;
			
		Sys_GraphicsPtr								m_pGraphics;

		math::Color4								m_clearClr;
		float										m_clearDepth;
		int											m_clearStencil;

		RenderTexturePtr							m_pGBuffer;
		RenderTexturePtr							m_pABuffer;

		ScreenQuadPtr								m_pScreenQuad;

		LightManagerPtr								m_pLightManager;

		MaterialPtr									m_pLightMaterial;

		MaterialPtr									m_pScreenQuadMaterial;

		math::Color4								m_globalAmbientColor;

		PostEffectManagerPtr						m_pPostEffectManager;

		std::list<CameraPtr>						m_cameras;

		EventDispatcherPtr							m_pEventDispatcher;

		MATRIX_BLOCK								m_matrixBlock;
	};
}
