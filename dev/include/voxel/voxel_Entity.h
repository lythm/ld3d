#pragma once

namespace ld3d
{
	namespace voxel
	{
		class Entity
		{
		public:
			Entity(void);
			virtual ~Entity(void);

		private:
			uint8*													m_data;

			uint32													m_size;

		};
	}
}
