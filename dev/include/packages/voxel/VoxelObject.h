#pragma once

namespace ld3d
{
	class VoxelObject : public GameObjectComponent
	{
	public:


	protected:

		VoxelObject(GameObjectManagerPtr pManager) : GameObjectComponent("Voxel.Object", pManager){}
		virtual ~VoxelObject(void){}

	};


}
