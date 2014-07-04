#pragma once

namespace ld3d
{
	class VoxelObjectRenderer : public GameObjectComponent
	{
	public:


	protected:
		VoxelObjectRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("Voxel.ObjectRenderer", pManager){}
		virtual ~VoxelObjectRenderer(void){}
		
	};
}
