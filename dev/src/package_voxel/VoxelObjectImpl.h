#pragma once

#include "packages/voxel/VoxelObject.h"

namespace ld3d
{
	class VoxelObjectImpl : public VoxelObject
	{
	public:
		VoxelObjectImpl(GameObjectManagerPtr pManager);
		virtual ~VoxelObjectImpl(void);

		const Version&								GetVersion() const;

	private:
		bool										OnAttach();
		void										OnDetach();
	};


}
