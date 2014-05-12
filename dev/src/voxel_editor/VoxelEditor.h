#pragma once

#include "core/GameInterface.h"

namespace ld3d
{
	namespace voxel
	{
		class VoxelEditor: public ld3d::GameInterface
		{
		public:
			VoxelEditor(void);
			virtual ~VoxelEditor(void);

			bool									Initialize(CoreApiPtr pCore);
			void									Release();
			bool									Update(float dt);

		};


	}
}