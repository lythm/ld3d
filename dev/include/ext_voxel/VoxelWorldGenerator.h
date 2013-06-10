#pragma once

namespace ld3d
{
	class VoxelWorldGenerator : public GameObjectComponent
	{
	public:
		VoxelWorldGenerator(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldGenerator(void);

		bool																OnAttach();
		void																OnDetach();

		void																RebuildWorld();

		const float&														GetSmooth() const;
		void																SetSmooth(const float& r);


		static VoxelWorldDataSetPtr											Generate(int sx, int sy, int sz);
		static VoxelWorldDataSetPtr											Generate_Perlin(int sx, int sy, int sz);
		static VoxelWorldDataSetPtr											Generate_Fractal(int sx, int sy, int sz, float h);

	private:

		void																OnSignaleGenerate(const prop_signal& s);
		prop_signal															_dummy();


		static float														_rand (float min, float max);
		static float														_fractal_rand(float v);
		static float														_fractal_avg_DiamondVals (int x, int z, int stride, int size, int segs, float *hm);
		static float														_fractal_avg_SquareVals (int x, int z, int stride, int size, float *hm);

		


	private:
		float																m_smooth;
	};
}
