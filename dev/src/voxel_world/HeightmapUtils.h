#pragma once
namespace ld3d
{
	class HeightmapUtils
	{
	private:
		HeightmapUtils(void);
		virtual ~HeightmapUtils(void);


	public:
		static bool								Fractal(float* height_map, int d, float s, int rand_seed);


	private:
		static float							_rand (float min, float max);
		static float							_fractal_rand(float v);
		static float							_fractal_avg_DiamondVals (int x, int z, int stride, int size, int segs, float *hm);
		static float							_fractal_avg_SquareVals (int x, int z, int stride, int size, float *hm);
	};


}