#pragma once

namespace ld3d
{
	class VoxelWorldGenerator : public GameObjectComponent
	{
	public:
		virtual void																RebuildWorld()						= 0;

		virtual const float&														GetSmooth() const					= 0;
		virtual void																SetSmooth(const float& r)			= 0;

	protected:
		VoxelWorldGenerator(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelWorldGenerator", pManager){}
		virtual ~VoxelWorldGenerator(void){}

	};
}
