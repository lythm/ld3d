#include "voxel_pch.h"
#include "voxel_VoxelUtils.h"



namespace ld3d
{
	namespace voxel
	{
		VoxelUtils::VoxelUtils(void)
		{
		}


		VoxelUtils::~VoxelUtils(void)
		{
		}
		Coord VoxelUtils::ToRegionOrigin(const Coord& c)
		{
			Coord region_coord = ToRegionCoord(c);

			region_coord.x *= REGION_SIZE;
			region_coord.y *= REGION_SIZE;
			region_coord.z *= REGION_SIZE;


			return region_coord;
		}
		Coord VoxelUtils::ToRegionCoord(const Coord& c)
		{
			int64 c_x = uint64(c.x) / (REGION_SIZE);
			int64 c_y = uint64(c.y) / (REGION_SIZE);
			int64 c_z = uint64(c.z) / (REGION_SIZE);
			
			return Coord((int32)c_x, (int32)c_y, (int32)c_z);
		}
		Coord VoxelUtils::ToChunkOrigin(const Coord& c)
		{
			Coord chunk_coord = ToChunkCoord(c);
			return chunk_coord * CHUNK_SIZE;

		}
		Coord VoxelUtils::ToChunkCoord(const Coord& c)
		{
			int64 c_x = uint64(c.x) / (CHUNK_SIZE);
			int64 c_y = uint64(c.y) / (CHUNK_SIZE);
			int64 c_z = uint64(c.z) / (CHUNK_SIZE);
			
			return Coord((int32)c_x, (int32)c_y, (int32)c_z);
		}
		bool VoxelUtils::Perlin(float* height_map, int d, int octaves,float freq,float amp,int seed)
		{
			PerlinNoise pn;
			
			pn.set_up(octaves, freq, amp, seed);

			for(int x = 0; x < d;++x)
			{
				for(int z = 0; z < d; ++z)
				{
					height_map[x * d + z] = (float)pn.Get(x, z);
				}
			}
			return true;
		}
		bool VoxelUtils::Fractal(float* height_map, int d, float s, int rand_seed)
		{
			int seed = rand_seed;

			float hscale = 1;

			float ratio = (float) pow (2.,-s);
			float scale = hscale * ratio;

			srand(seed);


			int e = math::closest_expo(d);

			d = e < d ? e << 1 : e;
			d += 1;

			//	memset(height_map, 0, sizeof(float) * d * d);
			//	float init_value = 0;

			//	height_map[0] = init_value;
			//	height_map[d - 1] = init_value;
			//	height_map[(d - 1) * d] = init_value;
			//	height_map[(d - 1) * d + d - 1] = init_value;

			int segs = d - 1;
			int stride = segs / 2;

			while(stride > 0)
			{
				for (int x=stride; x<segs; x+=stride) 
				{
					for (int z=stride; z<segs; z+=stride)
					{
						height_map[(x * d) + z] =
							scale * _fractal_rand (.5f) +
							_fractal_avg_SquareVals (x, z, stride, d, height_map);
						z += stride;
					}
					x += stride;
				}

				int oddline = 0;
				for (int x=0; x<segs; x+=stride) 
				{
					oddline = (oddline == 0);
					for (int z=0; z<segs; z+=stride)
					{
						if ((oddline) && !z)
						{
							z +=stride;
						}

						height_map[(x * d) + z] =
							scale * _fractal_rand (.5f) +
							_fractal_avg_DiamondVals (x, z, stride, d, segs, height_map);

						if (x==0)
						{
							height_map[(segs*d) + z] = height_map[(x * d) + z];
						}
						if (z==0)
						{
							height_map[(x*d) + segs] = height_map[(x * d) + z];
						}

						z +=stride;
					}
				}

				scale *= ratio;
				stride >>= 1;
			}

			return true;
		}
		float VoxelUtils::_rand (float min, float max)
		{
			int r = rand();
			float x = (float)(r & 0x7fff) / (float)0x7fff;
			return (x * (max - min) + min);
		} 
		float VoxelUtils::_fractal_rand(float v)
		{
			return _rand(-v, v);
		}
		float VoxelUtils::_fractal_avg_DiamondVals (int x, int z, int stride, int size, int segs, float *hm)
		{
			if (x == 0)
			{
				return ((float) (hm[(x*size) + z-stride] +
					hm[(x*size) + z+stride] +
					hm[((segs-stride)*size) + z] +
					hm[((x+stride)*size) + z]) * .25f);
			}
			else if (x == size-1)
			{
				return ((float) (hm[(x*size) + z-stride] +
					hm[(x*size) + z+stride] +
					hm[((x-stride)*size) + z] +
					hm[((0+stride)*size) + z]) * .25f);
			}
			else if (z == 0)
			{
				return ((float) (hm[((x-stride)*size) + z] +
					hm[((x+stride)*size) + z] +
					hm[(x*size) + z+stride] +
					hm[(x*size) + segs-stride]) * .25f);
			}
			else if (z == size-1)
			{
				return ((float) (hm[((x-stride)*size) + z] +
					hm[((x+stride)*size) + z] +
					hm[(x*size) + z-stride] +
					hm[(x*size) + 0+stride]) * .25f);
			}


			return ((float) (hm[((x-stride)*size) + z] +
				hm[((x+stride)*size) + z] +
				hm[(x*size) + z-stride] +
				hm[(x*size) + z+stride]) * .25f);
		}

		float VoxelUtils::_fractal_avg_SquareVals (int x, int z, int stride, int size, float *hm)
		{
			return ((float) (hm[((x-stride)*size) + z-stride] +
				hm[((x-stride)*size) + z+stride] +
				hm[((x+stride)*size) + z-stride] +
				hm[((x+stride)*size) + z+stride]) * .25f);
		}
		Coord VoxelUtils::ChunkToChunk(const ChunkKey& k1, const Coord& c, const ChunkKey& k2)
		{
			Coord r = c;
			r += k1.ToChunkOrigin();
			r -= k2.ToChunkOrigin();

			return r;
		}
	}
}

