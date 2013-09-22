#pragma once

namespace ld3d
{
	class VoxelObject : public GameObjectComponent
	{
	public:
		VoxelObject(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelObject", pManager){}
		virtual ~VoxelObject(void){}

	};


}
