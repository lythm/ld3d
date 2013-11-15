#pragma once


namespace ld3d
{
	class VoxelWorldCollisionData : public GameObjectComponent
	{
	public:



	protected:
		VoxelWorldCollisionData(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelWorldCollisionData", pManager){}
		virtual ~VoxelWorldCollisionData(void){}
	};


}