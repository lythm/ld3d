#pragma once


namespace ld3d
{
	class EXPORT_CLASS Light_Spot : public GameObjectComponent
	{
	public:
		Light_Spot(GameObjectManagerPtr pManager);
		virtual ~Light_Spot(void);

		void										Update(float dt);
		SpotLightPtr								GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		SpotLightPtr								m_pLight;
	};


}