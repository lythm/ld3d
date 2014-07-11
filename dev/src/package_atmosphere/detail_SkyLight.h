#pragma once


namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			namespace detail
			{
				class SkyLight : public Light
				{
				public:
					SkyLight(void);
					virtual ~SkyLight(void);

					bool								Create(RenderManagerPtr pRenderManager);
					void								Release();
					void								RenderLight(RenderManagerPtr pRenderer);

					void								RenderShadowMap(RenderManagerPtr pRenderer);

					RenderTexturePtr					GetShadowMap();

					void								SetCastShadow(const bool& bCast);

					void								ResizeShadowMap();

					void								SetLightDir(const math::Vector3& dir);
					const math::Vector3&				GetLightDir() const;
				private:
					bool								CreateShadowMap(int w, int h, G_FORMAT format);

				private:

					math::Vector3						m_dir;
					
					MaterialPtr							m_pMaterial;
					RenderTexturePtr					m_pShadowMap;

					RenderManagerPtr					m_pRenderManager;

					math::Matrix44						m_lightTM;
				};


			}
		}
	}
}