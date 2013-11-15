#pragma once

namespace ld3d
{
	class VoxelObjectRenderer : public GameObjectComponent
	{
	public:


	protected:
		VoxelObjectRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelObjectRenderer", pManager){}
		virtual ~VoxelObjectRenderer(void){}
		
	};
}
