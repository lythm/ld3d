#pragma once

namespace ld3d
{
	class VoxelWorldRenderer : public GameObjectComponent
	{
	public:
		VoxelWorldRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRenderer(void);

		void										Update();
		const Version&								GetVersion() const;

		void										UpdateVoxelWorld(VoxelWorldPtr pWorld);

	private:
		bool										OnAttach();
		void										OnDetach();

		void										on_event_frustumcull(EventPtr pEvent);
	private:

		EventDispatcher::EventHandlerHandle			m_hFrustumCull;
		VoxelWorldRenderDataPtr						m_pRenderData;
		VoxelWorldPtr								m_pWorld;
	};
}
