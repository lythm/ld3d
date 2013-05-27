#pragma once

namespace ld3d
{
	struct Voxel;
	class VoxelWorldGenerator
	{
	public:
		
		static std::vector<Voxel*>											Generate(VoxelPoolPtr pPool, int sx, int sy, int sz);


	private:

		VoxelWorldGenerator(void);
		virtual ~VoxelWorldGenerator(void);
	};


}
