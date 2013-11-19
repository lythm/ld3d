#include "voxel_pch.h"
#include "VoxelWorldUtils.h"
#include "VoxelWorldChunk.h"
#include "VoxelWorldMesh.h"
#include "VoxelWorldRegion.h"

namespace ld3d
{
	uint32 VoxelWorldUtils::chunk_local_to_index(uint32 x, uint32 y, uint32 z)
	{
		return x + z * VOXEL_WORLD_CHUNK_SIZE + y * VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE;
	}
	void VoxelWorldUtils::GenChunkMesh(VoxelWorldChunk* pChunk)
	{
		VoxelWorldRegion* pRegion = pChunk->GetRegion();

		uint32 c_x, c_y, c_z;

		math::Vector3 chunk_coord = pChunk->GetChunkCoord();

		c_x = (uint32)chunk_coord.x;
		c_y = (uint32)chunk_coord.y;
		c_z = (uint32)chunk_coord.z;


		std::vector<VoxelFace> mesh;

		uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE];

		memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

		// -x axis
		for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					if(pRegion->Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}

					if(pRegion->Empty(c_x + x - 1, c_y + y, c_z + z))
					{
						int index = chunk_local_to_index(x, y, z);
						faces[y][z] = pChunk->GetBlock(index);
						count++;
					}
				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(x, r[i].x1, r[i].y1);
				f.verts[1] = math::Vector3(x, r[i].x1, r[i].y2 + 1);
				f.verts[2] = math::Vector3(x, r[i].x2 + 1, r[i].y1);
				f.verts[3] = math::Vector3(x, r[i].x2 + 1, r[i].y2 + 1);

				math::Vector2 uv_scale;
				uv_scale.x = r[i].y2 + 1 - r[i].y1;
				uv_scale.y = r[i].x2 + 1 - r[i].x1;

				f.uv[0] = math::Vector2(uv_scale.x, 0);
				f.uv[1] = math::Vector2(0, 0);
				f.uv[2] = math::Vector2(uv_scale.x, uv_scale.y);
				f.uv[3] = math::Vector2(0, uv_scale.y);

				f.normal = math::Vector3(-1, 0, 0);
				f.type = r[i].type;
				mesh.push_back(f);
			}

		}

		// +x axis
		for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					if(pRegion->Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}

					if(pRegion->Empty(c_x + x + 1, c_y + y, c_z + z))
					{
						int index = chunk_local_to_index(x, y, z);
						faces[y][z] = pChunk->GetBlock(index);
						count++;
					}
				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(x + 1, r[i].x1, r[i].y1);
				f.verts[1] = math::Vector3(x + 1, r[i].x2 + 1, r[i].y1);
				f.verts[2] = math::Vector3(x + 1, r[i].x1, r[i].y2 + 1);
				f.verts[3] = math::Vector3(x + 1, r[i].x2 + 1, r[i].y2 + 1);
				f.normal = math::Vector3(1, 0, 0);

				math::Vector2 uv_scale;
				uv_scale.x = r[i].y2 + 1 - r[i].y1;
				uv_scale.y = r[i].x2 + 1 - r[i].x1;

				f.uv[0] = math::Vector2(0, 0);
				f.uv[1] = math::Vector2(0, uv_scale.y);
				f.uv[2] = math::Vector2(uv_scale.x, 0);
				f.uv[3] = math::Vector2(uv_scale.x, uv_scale.y);

				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// -y axis
		for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					int index = chunk_local_to_index(x, y, z);

					if(pRegion->Empty(c_x + x, c_y + y, c_z + z) || (c_y + y) == 0)
					{
						continue;
					}
					if(pRegion->Empty(c_x + x, c_y + y - 1, c_z + z))
					{
						int index = chunk_local_to_index(x, y, z);
						faces[x][z] = pChunk->GetBlock(index);
						count++;
					}
				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, y, r[i].y1);
				f.verts[1] = math::Vector3(r[i].x2 + 1, y, r[i].y1);
				f.verts[2] = math::Vector3(r[i].x1, y, r[i].y2 + 1);
				f.verts[3] = math::Vector3(r[i].x2 + 1, y, r[i].y2 + 1);
				f.normal = math::Vector3(0, -1, 0);

				math::Vector2 uv_scale;
				uv_scale.x = r[i].x2 + 1 - r[i].x1;
				uv_scale.y = r[i].y2 + 1 - r[i].y1;

				f.uv[0] = math::Vector2(0, uv_scale.y);
				f.uv[1] = math::Vector2(uv_scale.x, uv_scale.y);
				f.uv[2] = math::Vector2(0, 0);
				f.uv[3] = math::Vector2(uv_scale.x, 0);

				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// +y axis
		for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
				{
					int index = chunk_local_to_index(x, y, z);

					if(pRegion->Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}
					if(pRegion->Empty(c_x + x, c_y + y + 1, c_z + z))
					{
						int index = chunk_local_to_index(x, y, z);
						faces[x][z] = pChunk->GetBlock(index);
						count++;
					}

				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, y + 1, r[i].y1);
				f.verts[1] = math::Vector3(r[i].x1, y + 1, r[i].y2 + 1);
				f.verts[2] = math::Vector3(r[i].x2 + 1, y + 1, r[i].y1);
				f.verts[3] = math::Vector3(r[i].x2 + 1, y + 1, r[i].y2 + 1);
				f.normal = math::Vector3(0, 1, 0);

				math::Vector2 uv_scale;
				uv_scale.x = r[i].x2 + 1 - r[i].x1;
				uv_scale.y = r[i].y2 + 1 - r[i].y1;

				f.uv[0] = math::Vector2(0, 0);
				f.uv[1] = math::Vector2(0, uv_scale.y);
				f.uv[2] = math::Vector2(uv_scale.x, 0);
				f.uv[3] = math::Vector2(uv_scale.x, uv_scale.y);

				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// -z axis
		for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
				{
					int index = chunk_local_to_index(x, y, z);

					if(pRegion->Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}
					if(pRegion->Empty(c_x + x, c_y + y, c_z + z - 1))
					{
						int index = chunk_local_to_index(x, y, z);
						faces[x][y] = pChunk->GetBlock(index);
						count++;
					}

				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, r[i].y1, z);
				f.verts[1] = math::Vector3(r[i].x1, r[i].y2 + 1, z);
				f.verts[2] = math::Vector3(r[i].x2 + 1, r[i].y1, z);
				f.verts[3] = math::Vector3(r[i].x2 + 1, r[i].y2 + 1, z);
				f.normal = math::Vector3(0, 0, -1);

				math::Vector2 uv_scale;
				uv_scale.x = r[i].x2 + 1 - r[i].x1;
				uv_scale.y = r[i].y2 + 1 - r[i].y1;

				f.uv[0] = math::Vector2(uv_scale.x, 0);
				f.uv[1] = math::Vector2(uv_scale.y, uv_scale.y);
				f.uv[2] = math::Vector2(0, 0);
				f.uv[3] = math::Vector2(0, uv_scale.y);

				f.type = r[i].type;
				mesh.push_back(f);
			}
		}

		// +z axis
		for(int z = 0; z < VOXEL_WORLD_CHUNK_SIZE; ++z)
		{
			memset(faces, VT_EMPTY, VOXEL_WORLD_CHUNK_SIZE * VOXEL_WORLD_CHUNK_SIZE);

			int count = 0;
			for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
				{
					int index = chunk_local_to_index(x, y, z);

					if(pRegion->Empty(c_x + x, c_y + y, c_z + z))
					{
						continue;
					}
					if(pRegion->Empty(c_x + x, c_y + y, c_z + z + 1))
					{
						int index = chunk_local_to_index(x, y, z);
						faces[x][y] = pChunk->GetBlock(index);
						count++;
					}

				}
			}
			if(count == 0)
			{
				continue;
			}
			std::vector<FaceRegion> r = ExtractRegion(faces);
			for(size_t i = 0; i < r.size(); ++i)
			{
				VoxelFace f;
				f.verts[0] = math::Vector3(r[i].x1, r[i].y1, z + 1);
				f.verts[1] = math::Vector3(r[i].x2 + 1, r[i].y1, z + 1);
				f.verts[2] = math::Vector3(r[i].x1, r[i].y2 + 1, z + 1);
				f.verts[3] = math::Vector3(r[i].x2 + 1, r[i].y2 + 1, z + 1);
				f.normal = math::Vector3(0, 0, 1);
				math::Vector2 uv_scale;
				uv_scale.x = r[i].x2 + 1 - r[i].x1;
				uv_scale.y = r[i].y2 + 1 - r[i].y1;

				f.uv[0] = math::Vector2(0, 0);
				f.uv[1] = math::Vector2(uv_scale.x, 0);
				f.uv[2] = math::Vector2(0, uv_scale.y);
				f.uv[3] = math::Vector2(uv_scale.x, uv_scale.y);

				f.type = r[i].type;

				mesh.push_back(f);
			}
		}

		std::sort(mesh.begin(), mesh.end(), [](VoxelFace& a,VoxelFace& b){return a.type < b.type;});

		VoxelWorldMesh* pMesh = pChunk->GetMesh();
		
		pMesh->Reset();

		VoxelWorldMesh::Subset sub;
		sub.type = VT_EMPTY;
		sub.vertexCount				= 0;
		sub.vertexBuffer			= nullptr;

		if(mesh.size() != 0)
		{
			sub.type = mesh[0].type;

			pMesh->AllocVertexBuffer(mesh.size() * 6);
			
			VoxelWorldMesh::VoxelVertex* pData = (VoxelWorldMesh::VoxelVertex*)pMesh->GetVertexBuffer();
			sub.vertexBuffer = pData;

			for(size_t i = 0; i < mesh.size(); ++i)
			{
				const VoxelFace& face = mesh[i];

				if(face.type != sub.type && sub.vertexCount != 0)
				{
					pMesh->AddSubset(sub);

					sub.type = face.type;
					sub.vertexCount = 0;
					sub.vertexBuffer = pData;
				}

				pData->pos = face.verts[0] + chunk_coord;
				pData->normal = face.normal;
				pData->uv = face.uv[0];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[1] + chunk_coord;
				pData->normal = face.normal;
				pData->uv = face.uv[1];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[2] + chunk_coord;
				pData->normal = face.normal;
				pData->uv = face.uv[2];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[1] + chunk_coord;
				pData->normal = face.normal;
				pData->uv = face.uv[1];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[3] + chunk_coord;
				pData->normal = face.normal;
				pData->uv = face.uv[3];
				++pData;
				sub.vertexCount++;

				pData->pos = face.verts[2] + chunk_coord;
				pData->normal = face.normal;
				pData->uv = face.uv[2];

				++pData;
				sub.vertexCount++;
			}
			pMesh->AddSubset(sub);
		}
	}
	std::vector<VoxelWorldUtils::FaceRegion> VoxelWorldUtils::ExtractRegion(uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE])
	{
		std::vector<FaceRegion> result;

		while(true)
		{
			FaceRegion r;
			if(false == FindMaxRegion(faces, r))
			{
				break;
			}

			assert(r.x2 >= r.x1);
			assert(r.y2 >= r.y1);

			result.push_back(r);

			for(int x = r.x1; x <= r.x2; ++x)
			{
				for(int y = r.y1; y <= r.y2; ++y)
				{
					faces[x][y] = VT_EMPTY;
				}
			}
		}


		return result;
	}
	bool VoxelWorldUtils::FindMaxRegion(uint8 faces[VOXEL_WORLD_CHUNK_SIZE][VOXEL_WORLD_CHUNK_SIZE], FaceRegion& r)
	{
		struct Stride
		{
			int x, y;
			int len;
			int type;
		};

		Stride max_v_s;
		max_v_s.len = 0;

		for(int x = 0; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
		{
			Stride s;
			s.len = 0;
			for(int y = 0; y < VOXEL_WORLD_CHUNK_SIZE; ++y)
			{
				if(faces[x][y] != VT_EMPTY)
				{
					s.x = x;
					s.y = y;
					s.type = faces[x][y];
					s.len = 1;
					break;
				}
			}

			if(s.len == 0)
			{
				continue;
			}

			for(int y = s.y + 1; y < VOXEL_WORLD_CHUNK_SIZE;++y)
			{
				if(faces[x][y] != s.type)
				{
					break;
				}
				s.len++;
			}

			if(max_v_s.len < s.len)
			{
				max_v_s = s;
			}
		}

		if(max_v_s.len == 0)
		{
			return false;
		}


		std::vector<Stride> h_strides;
		Stride max_h_stride;
		max_h_stride.len = 0;


		for(int y = max_v_s.y; y < max_v_s.y + max_v_s.len; ++y)
		{
			Stride s;
			s.len = 0;
			s.y = y;
			s.type = max_v_s.type;

			for(int x = max_v_s.x; x < VOXEL_WORLD_CHUNK_SIZE; ++x)
			{
				if(faces[x][y] != s.type)
				{
					break;
				}

				s.len ++;
			}

			s.x = max_v_s.x;

			for(int x = max_v_s.x - 1; x >= 0; --x)
			{
				if(faces[x][y] != s.type)
				{
					break;
				}

				s.len ++;
				s.x = x;
			}

			h_strides.push_back(s);

			if(max_h_stride.len < s.len)
			{
				max_h_stride = s;
			}
		}

		int max_area = 0;

		for(int i = 0; i < h_strides.size(); ++i)
		{
			FaceRegion region;
			Stride s = h_strides[i];

			region.x1 = s.x;
			region.y1 = s.y;
			region.type = s.type;
			int v_len = 1;

			for(int ii = i + 1; ii < h_strides.size(); ++ii)
			{
				if(s.x < h_strides[ii].x || (s.x + s.len - 1) > (h_strides[ii].x + h_strides[ii].len - 1))
				{
					break;
				}

				v_len ++;
			}

			for(int ii = i - 1; ii >= 0; --ii)
			{
				if(s.x < h_strides[ii].x || (s.x + s.len - 1) > (h_strides[ii].x + h_strides[ii].len - 1))
				{
					break;
				}

				v_len ++;
				region.y1--;
			}

			region.x2 = region.x1 + s.len - 1;
			region.y2 = region.y1 + v_len - 1;
			int area = v_len * s.len;
			if(max_area < area)
			{
				max_area = area;
				r = region;
			}

		}

		return true;
	}
}
