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

			void									_on_key_state(ld3d::EventPtr pEvent);
		private:
			GameObjectPtr							m_pCamera;
			GameObjectPtr							m_pGrid;

			CoreApiPtr								m_pCore;
		};


	}
}