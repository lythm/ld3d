#pragma once

#include "atmosphere/SkyLight.h"



namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			namespace detail
			{
				class SkyLight;
			};
			class Impl_SkyLight : public SkyLight
			{
			public:
				Impl_SkyLight(GameObjectManagerPtr pManager);
				virtual ~Impl_SkyLight(void);



			private:
				
				void										Update(float dt);
				LightPtr									GetLight();


				bool										OnSerialize(DataStream* pStream);
				bool										OnUnSerialize(DataStream* pStream, const Version& version );

				void										EnableShadow(bool enable);

				void										SetLightDir(const math::Vector3& dir);
				const math::Vector3&						GetLightDir() const;
			private:
				bool										OnAttach();
				void										OnDetach();
			private:
				RenderManagerPtr							m_pRenderManager;
				std::shared_ptr<detail::SkyLight>			m_pLight;
			private:

			};


		}
	}
}