#include "package_atmosphere_pch.h"
#include "Impl_SkyDome.h"

namespace ld3d
{
	namespace atmosphere
	{
		Impl_SkyDome::Impl_SkyDome(GameObjectManagerPtr pManager) : SkyDome(pManager)
		{
			SetVersion(g_packageVersion);
		}


		Impl_SkyDome::~Impl_SkyDome(void)
		{
		}
		bool Impl_SkyDome::OnAttach()
		{
			return true;
		}
		void Impl_SkyDome::OnDetach()
		{
			ClearPropertySet();
		}
		Impl_SkyDome::Vertex*	Impl_SkyDome::CreateSkyDome()
		{

			return nullptr;
		}
		void Impl_SkyDome::CreateIcoSphere(std::vector<math::Vector3>& geo, std::vector<int>& indices, int refine_lvl)
		{
			
			std::map<int64, int> cache;
			

			using namespace math;
			int index = 0;

			// create 12 vertices of a icosahedron
			float t = (1.0f + sqrtf(5.0f)) / 2.0f;

			AddVertex(geo, Vector3(-1,  t,  0));
			AddVertex(geo, Vector3( 1,  t,  0));
			AddVertex(geo, Vector3(-1, -t,  0));
			AddVertex(geo, Vector3( 1, -t,  0));

			AddVertex(geo, Vector3( 0, -1,  t));
			AddVertex(geo, Vector3( 0,  1,  t));
			AddVertex(geo, Vector3( 0, -1, -t));
			AddVertex(geo, Vector3( 0,  1, -t));

			AddVertex(geo, Vector3( t,  0, -1));
			AddVertex(geo, Vector3( t,  0,  1));
			AddVertex(geo, Vector3(-t,  0, -1));
			AddVertex(geo, Vector3(-t,  0,  1));

			std::vector<Triangle> faces;


			// 5 faces around point 0
			faces.push_back(Triangle(0, 11, 5));
			faces.push_back(Triangle(0, 5, 1));
			faces.push_back(Triangle(0, 1, 7));
			faces.push_back(Triangle(0, 7, 10));
			faces.push_back(Triangle(0, 10, 11));

			// 5 adjacent faces 
			faces.push_back(Triangle(1, 5, 9));
			faces.push_back(Triangle(5, 11, 4));
			faces.push_back(Triangle(11, 10, 2));
			faces.push_back(Triangle(10, 7, 6));
			faces.push_back(Triangle(7, 1, 8));

			// 5 faces around point 3
			faces.push_back(Triangle(3, 9, 4));
			faces.push_back(Triangle(3, 4, 2));
			faces.push_back(Triangle(3, 2, 6));
			faces.push_back(Triangle(3, 6, 8));
			faces.push_back(Triangle(3, 8, 9));

			// 5 adjacent faces 
			faces.push_back(Triangle(4, 9, 5));
			faces.push_back(Triangle(2, 4, 11));
			faces.push_back(Triangle(6, 2, 10));
			faces.push_back(Triangle(8, 6, 7));
			faces.push_back(Triangle(9, 8, 1));


			// refine triangles
			for (int i = 0; i < refine_lvl; i++)
			{
				std::vector<Triangle> faces2;

				for(auto tri : faces)
				{
					// replace triangle by 4 triangles
					int a = GetMidpoint(geo, tri.v1, tri.v2, cache);
					int b = GetMidpoint(geo, tri.v2, tri.v3, cache);
					int c = GetMidpoint(geo, tri.v3, tri.v1, cache);

					faces2.push_back(Triangle(tri.v1, a, c));
					faces2.push_back(Triangle(tri.v2, b, a));
					faces2.push_back(Triangle(tri.v3, c, b));
					faces2.push_back(Triangle(a, b, c));
				}
				faces = faces2;
			}

			// done, now add triangles to mesh
			for (auto tri : faces)
			{
				indices.push_back(tri.v1);
				indices.push_back(tri.v2);
				indices.push_back(tri.v3);
			}
		}
		int Impl_SkyDome::GetMidpoint(std::vector<math::Vector3>& geo, int p1, int p2, std::map<int64, int>& cache)
		{
			bool firstIsSmaller = p1 < p2;

			int64 smallerIndex = firstIsSmaller ? p1 : p2;
			int64 greaterIndex = firstIsSmaller ? p2 : p1;

			int64 key = (smallerIndex << 32) + greaterIndex;

			auto it = cache.find(key);
			if(it != cache.end())
			{
				return it->second;
			}
			using namespace math;

			Vector3 point1 = geo[p1];
			Vector3 point2 = geo[p2];

			Vector3 middle = Vector3(
				(point1.x + point2.x) / 2.0f, 
				(point1.y + point2.y) / 2.0f, 
				(point1.z + point2.z) / 2.0f);

			// add vertex makes sure point is on unit sphere
			int i = AddVertex(geo, middle); 

			cache[key] = i;
			return i;
		}
		int Impl_SkyDome::AddVertex(std::vector<math::Vector3>& geo, const math::Vector3& v)
		{
			math::Vector3 vertex = v;
			vertex.Normalize();

			geo.push_back(vertex);

			return (int)geo.size();
		}
	}
}