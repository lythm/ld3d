#pragma once

#include "packages/voxel/VoxelObjectRenderer.h"

namespace ld3d
{
	class VoxelObjectRendererImpl : public VoxelObjectRenderer
	{
	public:
		VoxelObjectRendererImpl(GameObjectManagerPtr pManager);
		virtual ~VoxelObjectRendererImpl(void);

		void										Update(float dt);
	private:
		bool										OnAttach();
		void										OnDetach();

	private:

	};
}
