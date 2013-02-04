
#pragma once


namespace ld3d
{
	class EXPORT_CLASS Light_Point : public GameObjectComponent
	{
	public:
		Light_Point(GameObjectManagerPtr pManager);
		virtual ~Light_Point(void);

		void										Update(float dt);
		PointLightPtr								GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderManagerPtr								m_pRenderManager;
		PointLightPtr								m_pLight;
	};

}