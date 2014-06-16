#pragma once


#include "packages/voxel/VoxelWorldRenderer.h"
namespace ld3d
{
	class VoxelWorldRendererImpl2 : public VoxelWorldRenderer
	{
	public:
		VoxelWorldRendererImpl2(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRendererImpl2(void);


		const bool&									GetShowBound();
		void										SetShowBound(const bool& show);


		void										Update(float dt);

		void										BindWorldViewPort(GameObjectPtr pNode);
		void										MoveViewPortTo(uint32 x, uint32 y, uint32 z);

		void										ResetWorld(voxel::WorldPtr pWorld);
		void										SetWorldViewPort(const voxel::Coord& center, uint32 size);
	private:
		void										on_event_frustumcull(EventPtr pEvent);
		bool										OnAttach();
		void										OnDetach();
	private:
		bool										m_bShowBound;

		GameObjectPtr								m_pViewPortRoot;

		voxel::WorldViewportPtr						m_pWorldVP;
		voxel::ChunkMeshizerPtr						m_pMeshizer;

		EventHandlerID								m_hFrustumCull;
	};
}
