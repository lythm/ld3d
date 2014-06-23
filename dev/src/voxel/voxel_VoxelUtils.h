#pragma once

#include "voxel/voxel_Coord.h"

namespace ld3d
{
	namespace voxel
	{
		class VoxelUtils
		{
		private:
			VoxelUtils(void);
			virtual ~VoxelUtils(void);


		public:
			static bool								Fractal(float* height_map, int d, float s, int rand_seed);

			static bool								Perlin(float* height_map, int d, int octaves,float freq,float amp,int seed);

			// in global space
			static Coord							ToRegionOrigin(const Coord& c);
			// global to region space
			static Coord							ToRegionCoord(const Coord& c);

			// in global space
			static Coord							ToChunkOrigin(const Coord& c);
			// global to chunk space
			static Coord							ToChunkCoord(const Coord& c);

			
		private:
			static float							_rand (float min, float max);
			static float							_fractal_rand(float v);
			static float							_fractal_avg_DiamondVals (int x, int z, int stride, int size, int segs, float *hm);
			static float							_fractal_avg_SquareVals (int x, int z, int stride, int size, float *hm);
		};
	}
}


