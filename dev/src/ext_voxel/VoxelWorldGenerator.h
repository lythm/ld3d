#pragma once

namespace ld3d
{
	struct Voxel;
	class VoxelWorldGenerator
	{
	public:
		
		static VoxelWorldDataSetPtr											Generate(int sx, int sy, int sz);
		static VoxelWorldDataSetPtr											Generate_Perlin(int sx, int sy, int sz);
		static VoxelWorldDataSetPtr											Generate_Fractal(int sx, int sy, int sz);

	private:

		static float														_rand (float min, float max);
		static float														_fractal_rand(float v);
		static float														_fractal_avg_DiamondVals (int x, int z, int stride, int size, int segs, float *hm);
		static float														_fractal_avg_SquareVals (int x, int z, int stride, int size, float *hm);




		VoxelWorldGenerator(void);
		virtual ~VoxelWorldGenerator(void);
	};


}
