#pragma once

namespace ld3d
{
	struct Voxel;
	class VoxelWorldGenerator
	{
	public:
		
		static VoxelWorldDataSetPtr											Generate(int sx, int sy, int sz);


	private:

		VoxelWorldGenerator(void);
		virtual ~VoxelWorldGenerator(void);
	};


}
