#pragma once

namespace ld3d
{
	namespace voxel
	{
		class Coord
		{
		public:
			Coord(int32 _x, int32 _y, int32 _z)
			{
				x = _x;
				y = _y;
				z = _z;
			}
			Coord()
			{
				x = 0;
				y = 0;
				z = 0;
			}

			int32						x;
			int32						y;
			int32						z;
		};
	}
}

