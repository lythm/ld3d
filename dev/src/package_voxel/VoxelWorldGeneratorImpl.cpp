#include "voxel_pch.h"
#include "VoxelWorldGeneratorImpl.h"

#include "VoxelWorldChunk.h"
#include "VoxelPool.h"
#include "VoxelWorldDataSet.h"
#include "VoxelWorldImpl.h"

#include <boost/random.hpp>

namespace ld3d
{
	VoxelWorldGeneratorImpl::VoxelWorldGeneratorImpl(GameObjectManagerPtr pManager) : VoxelWorldGenerator(pManager)
	{
		m_smooth = 0.6f;
	}


	VoxelWorldGeneratorImpl::~VoxelWorldGeneratorImpl(void)
	{
	}
	const float& VoxelWorldGeneratorImpl::GetSmooth() const
	{
		return m_smooth;
	}
	void VoxelWorldGeneratorImpl::SetSmooth(const float& r)
	{
		m_smooth = r;

		m_smooth = m_smooth > 1.0f ? 1.0f : m_smooth;
		m_smooth = m_smooth < 0.0f ? 0.0f : m_smooth;
	}
	void VoxelWorldGeneratorImpl::RebuildWorld()
	{
		VoxelWorldImplPtr pWorld = std::dynamic_pointer_cast<VoxelWorldImpl>(GetGameObject()->GetComponent("VoxelWorld"));

		if(pWorld == nullptr)
		{
			return;
		}
		m_pManager->logger() << "Rebuilding Voxel world..." << "\n";

		int tick = os_get_tick();

		VoxelWorldDataSetPtr pDataSet = pWorld->GetDataSet();
		if(pDataSet != nullptr)
		{
			pDataSet->Release();
		}

		pDataSet = Generate_Fractal(pWorld->GetWorldSizeX(), pWorld->GetWorldSizeY(), pWorld->GetWorldSizeZ(), m_smooth);
		pDataSet->UpdateMesh();

		pWorld->SetDataSet(pDataSet);

		tick = os_get_tick() - tick;
		
		m_pManager->logger() << "Voxel world rebuilt.(" << pDataSet->GetFaceCount() << " triangles in " << float(tick) / 1000.0f << "s).\n";
		
	}
	void VoxelWorldGeneratorImpl::OnSignaleGenerate(const prop_signal& s)
	{
		RebuildWorld();
		static bool b = false;
		m_pManager->GetDTCoreApi()->Inspector_SetPropertyVisible("VoxelWorldGeneratorImpl", "Smooth", b);
		m_pManager->GetDTCoreApi()->Inspector_AdjustLayout();

		b = !b;
	}
	prop_signal VoxelWorldGeneratorImpl::_dummy()
	{
		return prop_signal();
	}
	bool VoxelWorldGeneratorImpl::OnAttach()
	{
		
		RegisterProperty<float, VoxelWorldGeneratorImpl>(this,
				"Smooth",
				&VoxelWorldGeneratorImpl::GetSmooth,
				&VoxelWorldGeneratorImpl::SetSmooth);

		RegisterProperty<prop_signal, VoxelWorldGeneratorImpl>(this,
				"Generate",
				&VoxelWorldGeneratorImpl::_dummy,
				&VoxelWorldGeneratorImpl::OnSignaleGenerate);

		
		return true;
	}
	void VoxelWorldGeneratorImpl::OnDetach()
	{
		ClearPropertySet();
	}


	VoxelWorldDataSetPtr VoxelWorldGeneratorImpl::Generate_Perlin(int sx, int sy, int sz)
	{
		PerlinNoise pl(7, 4, 1, os_get_tick());


		VoxelWorldDataSetPtr pDataSet = VoxelWorldDataSetPtr(new VoxelWorldDataSet);

		pDataSet->Initialize(sx, sy, sz);

		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				float h = pl.Get(float(x) / float(sx), float(z) / float(sz));

				//h = h / 2.0f;

				//h += 0.5;

				h *= sy;

				for(int y = 0; y < (int)h; ++y)
				{
					pDataSet->AddVoxel(VT_STONE, x, y, z);
				}
			}
		}

		return pDataSet;
	}
	VoxelWorldDataSetPtr VoxelWorldGeneratorImpl::Generate(int sx, int sy, int sz)
	{
		VoxelWorldDataSetPtr pDataSet = VoxelWorldDataSetPtr(new VoxelWorldDataSet);

		pDataSet->Initialize(sx, sy, sz);


		for(int y = 0; y < sy; ++y)
		{
			for(int x = 0; x < sx; ++x)
			{
				for(int z = 0; z < sz; ++z)
				{
					if(y == 0)
					{
						pDataSet->AddVoxel(VT_GOLD, x, y, z);
					}
					else
					{
						pDataSet->AddVoxel(VT_STONE, x, y, z);
					}
				}
			}
		}


		/*for(int x = 0; x < sx; ++x)
		{
		for(int z = 0; z < sz; ++z)
		{
		int yy = sinf(x / 10.0f ) * sy  + (sinf(z / 10.0f)) * sy + 1;
		for(int y = 0; y < yy; ++y)
		{
		pDataSet->AddVoxel(VT_STONE, x, y, z);
		}
		}
		}*/

		//boost::random::mt19937 rng;         // produces randomness out of thin air
		//                                  // see pseudo-random number generators
		//
		//                                  // distribution that maps to 1..6
		//                                  // see random number distributions
		//
		//
		//for(int x = 0; x < sx; ++x)
		//{
		//	for(int z = 0; z < sz; ++z)
		//	{
		//		for(int y = 0; y < sy; ++y)
		//		{
		//			boost::random::uniform_int_distribution<> gen(0,y);

		//			int ret = gen(rng);
		//			if(ret == 0)
		//			{
		//				pDataSet->AddVoxel(VT_STONE, x, y, z);
		//			}
		//		}
		//	}
		//}


		//boost::random::mt19937 rng;         // produces randomness out of thin air
		//		for(int x = 0; x < sx; ++x)
		//{
		//	for(int z = 0; z < sz; ++z)
		//	{
		//		boost::random::uniform_int_distribution<> gen(1,sy);

		//		int h = gen(rng);

		//		//int h = sqrt(sy - (x - sx / 2) * (x - sx /2)  - (z - sz/2) * (z- sz/2));

		//		for(int y = 0; y < h; ++y)
		//		{
		//			pDataSet->AddVoxel(VT_STONE, x, y, z);
		//		}
		//	}
		//}

		return pDataSet;
	}
	VoxelWorldDataSetPtr VoxelWorldGeneratorImpl::Generate_Fractal(int sx, int sy, int sz, float h)
	{
		int seed = os_get_tick();
		float hscale = 1;

		float ratio = (float) pow (2.,-h);
		float scale = hscale * ratio;

		srand(seed);


		VoxelWorldDataSetPtr pDataSet = VoxelWorldDataSetPtr(new VoxelWorldDataSet);

		pDataSet->Initialize(sx, sy, sz);

		int d = sx < sz ? sz : sx;

		int e = math::closest_expo(d);

		d = e < d ? e << 1 : e;
		d += 1;

		float* height_map = new float[d * d];

		memset(height_map, 0, sizeof(float) * d * d);


		float init_value = 0;

		height_map[0] = init_value;
		height_map[d - 1] = init_value;
		height_map[(d - 1) * d] = init_value;
		height_map[(d - 1) * d + d - 1] = init_value;

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

		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				float h = height_map[x * d + z];

				//h *= 0.5;
				//h += 0.5;


				h *= sy;
				h = h > sy ? sy : h;
				//h = h < 1 ? 1 : h;

				for(int y = 0; y < (int)h; ++y)
				{
					if(y < 5)
					{
						pDataSet->AddVoxel(VT_GRASS, x, y, z);
					}
					else if( y < 10)
					{
						pDataSet->AddVoxel(VT_STONE, x, y, z);
					}
					else
					{
						pDataSet->AddVoxel(VT_SILVER, x, y, z);
					}
				}
			}
		}


		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				uint8 t = pDataSet->GetVoxelType(x, 0, z);
				if(t != VT_EMPTY)
				{
					continue;
				}
				pDataSet->AddVoxel(VT_WATER, x, 0, z);
				
			}
		}

		for(int x = 0; x < sx; ++x)
		{
			for(int z = 0; z < sz; ++z)
			{
				uint8 t = pDataSet->GetVoxelType(x + 1, 0, z);
				
				if(t != VT_EMPTY && t != VT_WATER)
				{
					pDataSet->ConvertVoxel(VT_BEACH, x + 1, 0, z);
				}

				t = pDataSet->GetVoxelType(x , 0, z + 1);
				
				if(t != VT_EMPTY && t != VT_WATER)
				{
					pDataSet->ConvertVoxel(VT_BEACH, x, 0, z + 1);
				}

				t = pDataSet->GetVoxelType(x , 0, z - 1);
				
				if(t != VT_EMPTY && t != VT_WATER)
				{
					pDataSet->ConvertVoxel(VT_BEACH, x, 0, z - 1);
				}

				t = pDataSet->GetVoxelType(x -1, 0, z);
				
				if(t != VT_EMPTY && t != VT_WATER)
				{
					pDataSet->ConvertVoxel(VT_BEACH, x - 1, 0, z);
				}


				pDataSet->AddVoxel(VT_WATER, x, 0, z);
				
			}
		}


		delete []height_map;

		return pDataSet;

	}
	
	float VoxelWorldGeneratorImpl::_rand (float min, float max)
	{
		int r = rand();
		float x = (float)(r & 0x7fff) / (float)0x7fff;
		return (x * (max - min) + min);
	} 
	float VoxelWorldGeneratorImpl::_fractal_rand(float v)
	{
		return _rand(-v, v);
	}
	float VoxelWorldGeneratorImpl::_fractal_avg_DiamondVals (int x, int z, int stride, int size, int segs, float *hm)
	{
		if (x == 0)
			return ((float) (hm[(x*size) + z-stride] +
			hm[(x*size) + z+stride] +
			hm[((segs-stride)*size) + z] +
			hm[((x+stride)*size) + z]) * .25f);
		else if (x == size-1)
			return ((float) (hm[(x*size) + z-stride] +
			hm[(x*size) + z+stride] +
			hm[((x-stride)*size) + z] +
			hm[((0+stride)*size) + z]) * .25f);
		else if (z == 0)
			return ((float) (hm[((x-stride)*size) + z] +
			hm[((x+stride)*size) + z] +
			hm[(x*size) + z+stride] +
			hm[(x*size) + segs-stride]) * .25f);
		else if (z == size-1)
			return ((float) (hm[((x-stride)*size) + z] +
			hm[((x+stride)*size) + z] +
			hm[(x*size) + z-stride] +
			hm[(x*size) + 0+stride]) * .25f);
		else
			return ((float) (hm[((x-stride)*size) + z] +
			hm[((x+stride)*size) + z] +
			hm[(x*size) + z-stride] +
			hm[(x*size) + z+stride]) * .25f);
	}

	float VoxelWorldGeneratorImpl::_fractal_avg_SquareVals (int x, int z, int stride, int size, float *hm)
	{
		return ((float) (hm[((x-stride)*size) + z-stride] +
			hm[((x-stride)*size) + z+stride] +
			hm[((x+stride)*size) + z-stride] +
			hm[((x+stride)*size) + z+stride]) * .25f);
	}
}