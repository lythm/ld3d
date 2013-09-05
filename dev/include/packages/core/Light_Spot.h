#pragma once


namespace ld3d
{
	class _DLL_CLASS Light_Spot : public GameObjectComponent
	{
	public:
		Light_Spot(GameObjectManagerPtr pManager);
		virtual ~Light_Spot(void);

		void										Update(float dt);
		SpotLightPtr								GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		SpotLightPtr								m_pLight;
	};


}