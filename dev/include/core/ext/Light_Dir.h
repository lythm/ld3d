#pragma once

namespace ld3d
{
	class EXPORT_CLASS Light_Dir : public GameObjectComponent
	{
	public:
		Light_Dir(GameObjectManagerPtr pManager);
		virtual ~Light_Dir(void);

		void										Update(float dt);
		DirectionalLightPtr							GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		DirectionalLightPtr							m_pLight;
	};
}
