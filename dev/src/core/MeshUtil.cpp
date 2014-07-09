#include "core_pch.h"
#include "core/MeshUtil.h"
#include "core/Mesh.h"
#include "core/VertexFormat.h"
#include "core/SubMesh.h"
#include "core_utils.h"
#include "core/Sys_Graphics.h"
#include "core/GPUBuffer.h"

namespace ld3d
{
	MeshUtil::MeshUtil(void)
	{
	}


	MeshUtil::~MeshUtil(void)
	{
	}
	MeshPtr MeshUtil::CreateCone(float range, float angle, float slice, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();

		VertexLayout format;
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		float radius = tanf(math::D2R(angle)) * range;
		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		int nVerts = int(slice * 6);
		Vertex* pVerts = (Vertex*)mem_alloc(sizeof(Vertex) * nVerts);

		int n = 0;
		for(int i = 0; i < slice; i++)
		{
			float th = 360.0f / float(slice) * i;
			// side
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;

			pVerts[n].normal = pVerts[n].pos;
			pVerts[n].normal.Normalize();

			n++;

			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;
			pVerts[n].normal = pVerts[n].pos;
			pVerts[n].normal.Normalize();
			n++ ;


			pVerts[n].pos.x = 0;
			pVerts[n].pos.z = 0;
			pVerts[n].pos.y = range;
			pVerts[n].normal = pVerts[n].pos;
			pVerts[n].normal.Normalize();
			n++ ;

			// bottom
			th = 360.0f / float(slice) * i;
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;

			pVerts[n].normal = math::Vector3(0, 0, -1);

			n++;

			pVerts[n].pos.x = 0;
			pVerts[n].pos.z = 0;
			pVerts[n].pos.y = 0;
			pVerts[n].normal = math::Vector3(0, 0, -1);
			n++ ;

			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;
			pVerts[n].normal = math::Vector3(0, 0, -1);
			n++ ;
		}

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(0, nullptr, sizeof(Vertex) * nVerts, pVerts, mats))
		{
			mem_free(pVerts);
			return MeshPtr();
		}

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 0, 0, nVerts, sizeof(Vertex), 0, 2, PT_TRIANGLE_LIST, format, G_FORMAT_R16_UINT);
		pMesh->AddSubMesh(pSub);

		mem_free(pVerts);
		return pMesh;
	}
	MeshPtr MeshUtil::CreatePlane(float size, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();

		VertexLayout format;
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		size = size / 2.0f;

		Vertex pVerts[] = 
		{
			// front
			{math::Vector3(-size, 0, -size), math::Vector3(0, 1, 0),},
			{math::Vector3(-size, 0, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, 0, size), math::Vector3(0, 1, 0),},


			{math::Vector3(-size, 0, -size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, 0, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, 0, -size), math::Vector3(0, 1, 0),},

		};

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(0, nullptr, sizeof(Vertex) * 6, pVerts, mats))
		{
			return MeshPtr();
		}

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 0, 0, 6, sizeof(Vertex), 0, 2, PT_TRIANGLE_LIST, format, G_FORMAT_R16_UINT);
		pMesh->AddSubMesh(pSub);

		return pMesh;
	}
	MeshPtr MeshUtil::CreateCube(float size, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();


		VertexLayout format;
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		size = size / 2.0f;
		Vertex pVerts[] = 
		{
			// front
			{math::Vector3(-size, size, -size), math::Vector3(0, 0, -1),},
			{math::Vector3(size, size, -size), math::Vector3(0, 0, -1),},
			{math::Vector3(size, -size, -size), math::Vector3(0, 0, -1),},
			{math::Vector3(-size, -size, -size), math::Vector3(0, 0, -1),},

			// back
			{math::Vector3(-size, size, size), math::Vector3(0, 0, 1),},
			{math::Vector3(size, size, size), math::Vector3(0, 0, 1),},
			{math::Vector3(size, -size, size), math::Vector3(0, 0, 1),},
			{math::Vector3(-size, -size, size), math::Vector3(0, 0, 1),},

			// top
			{math::Vector3(-size, size, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, size, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, size, -size), math::Vector3(0, 1, 0),},
			{math::Vector3(-size, size, -size), math::Vector3(0, 1, 0),},
			// bottom
			{math::Vector3(-size, -size, size), math::Vector3(0, -1, 0),},
			{math::Vector3(size, -size, size), math::Vector3(0, -1, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(0, -1, 0),},
			{math::Vector3(-size, -size, -size), math::Vector3(0, -1, 0),},

			// left
			{math::Vector3(-size, size, size), math::Vector3(-1, 0, 0),},
			{math::Vector3(-size, size, -size), math::Vector3(-1, 0, 0),},
			{math::Vector3(-size, -size, -size), math::Vector3(-1, 0, 0),},
			{math::Vector3(-size, -size, size), math::Vector3(-1, 0, 0),},
			// right
			{math::Vector3(size, size, size), math::Vector3(1, 0, 0),},
			{math::Vector3(size, size, -size), math::Vector3(1, 0, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(1, 0, 0),},
			{math::Vector3(size, -size, size), math::Vector3(1, 0, 0),},
		};

		uint16 pIndice[] = 
		{
			// front
			0, 1, 2,
			0, 2, 3,

			// back
			4, 6, 5, 
			4, 7, 6,


			//top
			8, 9, 10,
			8, 10, 11,

			// bottom
			12, 14, 13,
			12, 15, 14,

			// left
			16, 17, 18,
			16, 18, 19,

			// right
			20, 22, 21,
			20, 23, 22,

		};


		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(sizeof(uint16) * 36, pIndice, sizeof(Vertex) * 24, pVerts, mats))
		{
			return MeshPtr();
		}

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 36, 0, 24, sizeof(Vertex), 0, 12, PT_TRIANGLE_LIST, format, G_FORMAT_R16_UINT);
		pMesh->AddSubMesh(pSub);

		return pMesh;
	}
	MeshPtr MeshUtil::CreateSphere(float radius, float slice, float stack, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();


		VertexLayout format;
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);


		int NumVertices = 0;
		math::Vector3* pPos = CreateSphere(radius, slice, stack, NumVertices);

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		Vertex* pVerts = (Vertex*)mem_alloc(sizeof(Vertex) * NumVertices);
		for(int i = 0; i < NumVertices; ++i)
		{
			pVerts[i].pos = pPos[i];
			pVerts[i].normal = pPos[i];
			pVerts[i].normal.Normalize();

		}

		mem_free(pPos);

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(0, NULL, sizeof(Vertex) * NumVertices, pVerts, mats))
		{
			mem_free(pVerts);
			return MeshPtr();
		}
		mem_free(pVerts);

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 0, 0, NumVertices, sizeof(Vertex), 0, NumVertices - 2, PT_TRIANGLE_STRIP, format, G_FORMAT_R16_UINT);

		pMesh->AddSubMesh(pSub);

		return pMesh;
	}

	math::Vector3* MeshUtil::CreateCube(float size, int& nVerts)
	{
		size = size / 2.0f;
		nVerts = 36;

		math::Vector3* pVerts = (math::Vector3*)mem_alloc(sizeof(math::Vector3) * nVerts);

		pVerts[0] = math::Vector3(-size, size, -size);
		pVerts[1] = math::Vector3(size, size, -size);
		pVerts[2] = math::Vector3(size, -size, -size);

		pVerts[3] = math::Vector3(-size, size, -size);
		pVerts[4] = math::Vector3(size, -size, -size);
		pVerts[5] = math::Vector3(-size, -size, -size);

		pVerts[6] = math::Vector3(-size, size, size);
		pVerts[7] = math::Vector3(size, -size, size);
		pVerts[8] = math::Vector3(size, size, size);

		pVerts[9] = math::Vector3(-size, size, size);
		pVerts[10] = math::Vector3(-size, -size, size);
		pVerts[11] = math::Vector3(size, -size, size);


		pVerts[12] = math::Vector3(-size, size, size);
		pVerts[13] = math::Vector3(size, size, size);
		pVerts[14] = math::Vector3(size, size, -size);

		pVerts[15] = math::Vector3(-size, size, size);
		pVerts[16] = math::Vector3(size, size, -size);
		pVerts[17] = math::Vector3(-size, size, -size);


		pVerts[18] = math::Vector3(-size, -size, size);
		pVerts[19] = math::Vector3(size, -size, -size);
		pVerts[20] = math::Vector3(size, -size, size);

		pVerts[21] = math::Vector3(-size, -size, size);
		pVerts[22] = math::Vector3(-size, -size, -size);
		pVerts[23] = math::Vector3(size, -size, -size);


		pVerts[24] = math::Vector3(-size, size, size);
		pVerts[25] = math::Vector3(-size, size, -size);
		pVerts[26] = math::Vector3(-size, -size, -size);

		pVerts[27] = math::Vector3(-size, size, size);
		pVerts[28] = math::Vector3(-size, -size, -size);
		pVerts[29] = math::Vector3(-size, -size, size);


		pVerts[30] = math::Vector3(size, size, size);
		pVerts[31] = math::Vector3(size, -size, -size);
		pVerts[32] = math::Vector3(size, size, -size);

		pVerts[33] = math::Vector3(size, size, size);
		pVerts[34] = math::Vector3(size, -size, size);
		pVerts[35] = math::Vector3(size, -size, -size);

		return pVerts;
	}
	math::Vector3* MeshUtil::CreateSphere(float radius, float slice, float stack, int& nVerts)
	{
#define DTOR (3.14f / 180.f)
		int theta, phi; 

		int dtheta = int(360 / slice); 
		int dphi = int(180 / stack); 

		nVerts = (int) ((360/dtheta) * (180/dphi) * 4); 

		math::Vector3* pVerts = (math::Vector3*)mem_alloc(sizeof(math::Vector3) * nVerts);

		int n = 0; 

		for (phi = 0; phi <= 180 - dphi; phi += (int)dphi) 
		{ 
			for (theta = 0; theta <= 360 - dtheta; theta += (int)dtheta) 
			{ 
				math::Vector3 pos;
				pos.x = radius * sinf(phi * DTOR) * cosf(theta * DTOR); 
				pos.y = radius * sinf(phi * DTOR) * sinf(theta * DTOR); 
				pos.z = radius * cosf(phi * DTOR); 
				pVerts[n] = pos;
				n++; 

				pos.x = radius * sinf((phi + dphi) * DTOR) * cosf(theta * DTOR); 
				pos.y = radius * sinf((phi + dphi) * DTOR) * sinf(theta * DTOR); 
				pos.z = radius * cosf((phi + dphi) * DTOR); 
				pVerts[n] = pos;
				n++; 

				pos.x = radius * sinf(phi * DTOR) * cosf((theta + dtheta) * DTOR); 
				pos.y = radius * sinf(phi * DTOR) * sinf((theta + dtheta) * DTOR); 
				pos.z = radius * cosf(phi * DTOR); 
				pVerts[n] = pos;
				n++; 

				if (phi > -180 && phi < 180) 
				{ 
					pos.x = radius * sinf((phi + dphi) * DTOR) * cosf((theta + dtheta) * DTOR); 
					pos.y = radius * sinf((phi + dphi) * DTOR) * sinf((theta + dtheta) * DTOR); 
					pos.z = radius * cosf((phi + dphi) * DTOR); 
					pVerts[n] = pos;
					n++; 
				} 
			} 
		}

		return pVerts;
	}
	math::Vector3* MeshUtil::CreateSpotLightCone(float range, float angle, float slice, int& nVerts)
	{
		float radius = tanf(math::D2R(angle)) * range;


		nVerts = int(slice * 6);
		math::Vector3* pVerts = (math::Vector3*)mem_alloc(sizeof(math::Vector3) * nVerts);

		int n = 0;
		for(int i = 0; i < slice; i++)
		{
			float th = 360.0f / float(slice) * i;
			// side
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++;

			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++ ;


			pVerts[n].x = 0;
			pVerts[n].z = 0;
			pVerts[n].y = 0;
			n++ ;

			// bottom
			th = 360.0f / float(slice) * i;
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++;

			pVerts[n].x = 0;
			pVerts[n].z = range;
			pVerts[n].y = 0;
			n++ ;

			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++ ;
		}

		return pVerts;
	}
	void MeshUtil::CreateUnitIcoSphere(int refine_lvl, std::vector<math::Vector3>& vb, std::vector<uint32>& ib, bool inv_vertex_order)
	{
		std::map<int64, int> cache;

		using namespace math;
		
		// create 12 vertices of a icosahedron
		float t = (1.0f + sqrtf(5.0f)) / 2.0f;

		IcoSphere_AddVertex(vb, Vector3(-1,  t,  0));
		IcoSphere_AddVertex(vb, Vector3( 1,  t,  0));
		IcoSphere_AddVertex(vb, Vector3(-1, -t,  0));
		IcoSphere_AddVertex(vb, Vector3( 1, -t,  0));

		IcoSphere_AddVertex(vb, Vector3( 0, -1,  t));
		IcoSphere_AddVertex(vb, Vector3( 0,  1,  t));
		IcoSphere_AddVertex(vb, Vector3( 0, -1, -t));
		IcoSphere_AddVertex(vb, Vector3( 0,  1, -t));

		IcoSphere_AddVertex(vb, Vector3( t,  0, -1));
		IcoSphere_AddVertex(vb, Vector3( t,  0,  1));
		IcoSphere_AddVertex(vb, Vector3(-t,  0, -1));
		IcoSphere_AddVertex(vb, Vector3(-t,  0,  1));

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
				int a = IcoSphere_GetMidPoint(vb, tri.v1, tri.v2, cache);
				int b = IcoSphere_GetMidPoint(vb, tri.v2, tri.v3, cache);
				int c = IcoSphere_GetMidPoint(vb, tri.v3, tri.v1, cache);

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
			ib.push_back(tri.v1);
			if(inv_vertex_order)
			{
				ib.push_back(tri.v3);
				ib.push_back(tri.v2);
			}
			else
			{
				ib.push_back(tri.v2);
				ib.push_back(tri.v3);
			}
		}
	}
	int MeshUtil::IcoSphere_GetMidPoint(std::vector<math::Vector3>& geo, int p1, int p2, std::map<int64, int>& cache)
	{
		bool firstIsSmaller = p1 < p2;

		int64 smallerIndex = firstIsSmaller ? p1 : p2;
		int64 greaterIndex = firstIsSmaller ? p2 : p1;

		uint64 key = (smallerIndex << 32) + greaterIndex;

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

		int i = IcoSphere_AddVertex(geo, middle); 

		cache[key] = i;
		return i;
	}
	int MeshUtil::IcoSphere_AddVertex(std::vector<math::Vector3>& geo, const math::Vector3& v)
	{
		math::Vector3 vertex = v;
		
		vertex.Normalize();

		geo.push_back(vertex);

		return (int)geo.size() - 1;
	}
	MeshPtr MeshUtil::CreateIcoSphere(float radius, int refine_lvl, MaterialPtr pMat, bool inv_vertex_order)
	{
		MeshPtr pMesh = alloc_object<Mesh>();


		VertexLayout format;
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);
		format.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		std::vector<math::Vector3>	vb;
		std::vector<uint32>			ib;
		CreateUnitIcoSphere(refine_lvl, vb, ib, inv_vertex_order);

		if(vb.size() == 0)
		{
			return nullptr;
		}
		Vertex* pVerts = (Vertex*)mem_alloc(sizeof(Vertex) * vb.size());
		for(size_t i = 0; i < vb.size(); ++i)
		{
			pVerts[i].pos = vb[i] * radius;
			pVerts[i].normal = vb[i];
			pVerts[i].normal.Normalize();

		}

		int32* pIndices = (int32*)mem_alloc(sizeof(int32) * ib.size());
		
		for(size_t i = 0; i < ib.size(); ++i)
		{
			pIndices[i] = ib[i];
		}

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(ib.size() * sizeof(int32), pIndices, sizeof(Vertex) * vb.size(), pVerts, mats))
		{
			mem_free(pVerts);
			return MeshPtr();
		}
		mem_free(pVerts);
		mem_free(pIndices);

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, ib.size(), 0, vb.size(), sizeof(Vertex), 0, ib.size() / 3, PT_TRIANGLE_LIST, format, G_FORMAT_R32_UINT);

		pMesh->AddSubMesh(pSub);

		return pMesh;
	}
}
