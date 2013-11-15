#pragma once

namespace ld3d
{
	class VoxelObject : public GameObjectComponent
	{
	public:


	protected:

		VoxelObject(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelObject", pManager){}
		virtual ~VoxelObject(void){}

	};


}
