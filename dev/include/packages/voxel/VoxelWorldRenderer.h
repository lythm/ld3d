#pragma once

namespace ld3d
{
	class VoxelWorldRenderer : public GameObjectComponent
	{
	public:
		

		virtual const bool&									GetShowBound()								= 0;
		virtual void										SetShowBound(const bool& show)				= 0;

	protected:
		VoxelWorldRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("VoxelWorldRenderer", pManager){}
		virtual ~VoxelWorldRenderer(void){}
	};
}
