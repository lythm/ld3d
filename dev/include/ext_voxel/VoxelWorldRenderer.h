#pragma once

namespace ld3d
{
	class VoxelWorldRenderer : public GameObjectComponent
	{
	public:
		VoxelWorldRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRenderer(void);

		void										Update();

		const bool&									GetShowBound();
		void										SetShowBound(const bool& show);

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version);

	private:
		bool										OnAttach();
		void										OnDetach();

		void										on_event_frustumcull(EventPtr pEvent);
	private:

		EventDispatcher::EventHandlerHandle			m_hFrustumCull;
		VoxelWorldRenderDataPtr						m_pRenderData;
		VoxelWorldPtr								m_pWorld;

		bool										m_bShowBound;

		BBoxRenderDataPtr							m_pBBoxRD;
	};
}
