#pragma once

namespace ld3d
{
	class EXPORT_CLASS Light_Sky : public GameObjectComponent
	{
	public:
		Light_Sky(GameObjectManagerPtr pManager);
		virtual ~Light_Sky(void);

		void										Update(float dt);
		SkyLightPtr									GetLight();


		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		SkyLightPtr									m_pLight;
	};


}
