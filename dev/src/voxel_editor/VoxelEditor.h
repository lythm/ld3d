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


		private:
			void									_on_cmd_set_camera_speed(const ld3d::CommandLine& cl, std::function<void (const std::string&)> writeln);
			void									_on_cmd_move_to(const ld3d::CommandLine& cl, std::function<void (const std::string&)> writeln);
			void									_on_key_state(ld3d::EventPtr pEvent);
			void									_on_resize(ld3d::EventPtr pEvent);
		private:
			GameObjectPtr							m_pCamera;
			GameObjectPtr							m_pGrid;

			CoreApiPtr								m_pCore;

			
			GameObjectPtr							m_pWorld;

			std::string*							m_debugInfo;
		};
	}
}
