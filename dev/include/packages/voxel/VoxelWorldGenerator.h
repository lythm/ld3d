#pragma once

namespace ld3d
{
	class VoxelWorldGenerator : public GameObjectComponent
	{
	public:
		VoxelWorldGenerator(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelWorldGenerator", pManager){}
		virtual ~VoxelWorldGenerator(void){}

		virtual void																RebuildWorld()						= 0;

		virtual const float&														GetSmooth() const					= 0;
		virtual void																SetSmooth(const float& r)			= 0;

	};
}
