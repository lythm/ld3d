#include "voxel_pch.h"
#include "VoxelWorldImpl.h"
#include "VoxelWorldChunk.h"
#include "VoxelWorldDataSet.h"
#include "VoxelWorldUtils.h"
#include "VoxelWorldMaterialManager.h"

namespace ld3d
{
	VoxelWorldImpl::VoxelWorldImpl(GameObjectManagerPtr pManager) : VoxelWorld(pManager)
	{
		m_voxelSize				= 1;
		m_worldSizeX			= 10;
		m_worldSizeY			= 2;
		m_worldSizeZ			= 10;
		
		SetVersion(g_packageVersion);

	}


	VoxelWorldImpl::~VoxelWorldImpl(void)
	{
	}
	void VoxelWorldImpl::Update(float dt)
	{
		if(m_pDataSet)
		{
			m_pDataSet->UpdateMesh();
		}
	}
	
	bool VoxelWorldImpl::OnAttach()
	{
		RegisterProperty<int, VoxelWorldImpl>(this,
				"Voxel Size",
				&VoxelWorldImpl::GetVoxelSize,
				&VoxelWorldImpl::SetVoxelSize);

		RegisterProperty<int, VoxelWorldImpl>(this,
				"World Size X",
				&VoxelWorldImpl::GetWorldSizeX,
				&VoxelWorldImpl::SetWorldSizeX);

		RegisterProperty<int, VoxelWorldImpl>(this,
				"World Size Y",
				&VoxelWorldImpl::GetWorldSizeY,
				&VoxelWorldImpl::SetWorldSizeY);

		RegisterProperty<int, VoxelWorldImpl>(this,
				"World Size Z",
				&VoxelWorldImpl::GetWorldSizeZ,
				&VoxelWorldImpl::SetWorldSizeZ);


		

		return true;
	}
	
	const int& VoxelWorldImpl::GetVoxelSize()
	{
		return m_voxelSize;
	}
	void VoxelWorldImpl::SetVoxelSize(const int& blockSize)
	{
		m_voxelSize = blockSize;
	}
	void VoxelWorldImpl::OnDetach()
	{
		ClearPropertySet();

		_release_and_reset(m_pDataSet);


	}
	const int& VoxelWorldImpl::GetWorldSizeX()
	{
		return m_worldSizeX;
	}
	void VoxelWorldImpl::SetWorldSizeX(const int& x)
	{
		m_worldSizeX = x;
	}

	const int& VoxelWorldImpl::GetWorldSizeY()
	{
		return m_worldSizeY;
	}
	void VoxelWorldImpl::SetWorldSizeY(const int& y)
	{
		m_worldSizeY = y;
	}

	const int& VoxelWorldImpl::GetWorldSizeZ()
	{
		return m_worldSizeZ;
	}
	void VoxelWorldImpl::SetWorldSizeZ(const int& z)
	{
		m_worldSizeZ = z;
	}
	
	VoxelWorldChunk* VoxelWorldImpl::FrustumCull(ViewFrustum* pVF)
	{
		if(m_pDataSet == nullptr)
		{
			return nullptr;
		}
		ViewFrustum vf = *pVF;

		math::Matrix44 world = m_pObject->GetWorldTransform();
		world.Invert();

		vf.Transform(world);
		
		return m_pDataSet->FrustumCull(vf);
	}
	
	VoxelWorldDataSetPtr VoxelWorldImpl::GetDataSet()
	{
		return m_pDataSet;
	}

	bool VoxelWorldImpl::OnSerialize(DataStream* pStream)
	{
		pStream->WriteInt32(m_worldSizeX);
		pStream->WriteInt32(m_worldSizeY);
		pStream->WriteInt32(m_worldSizeZ);
		pStream->WriteInt32(m_voxelSize);

		if(m_pDataSet == nullptr)
		{
			pStream->WriteInt32(0);
			return true;
		}

		return m_pDataSet->Serialize(pStream);
	}
	bool VoxelWorldImpl::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}

		m_worldSizeX = pStream->ReadInt32();
		m_worldSizeY = pStream->ReadInt32();
		m_worldSizeZ = pStream->ReadInt32();
		m_voxelSize = pStream->ReadInt32();

		if(m_pDataSet != nullptr)
		{
			m_pDataSet->Release();
		}
		m_pDataSet = m_pManager->alloc_object<VoxelWorldDataSet>();

		m_pDataSet->Initialize(m_worldSizeX, m_worldSizeY, m_worldSizeZ);
		
		return m_pDataSet->UnSerialize(pStream);
	}
	void VoxelWorldImpl::SetDataSet(VoxelWorldDataSetPtr pDataSet)
	{
		if(m_pDataSet != nullptr)
		{
			m_pDataSet->Release();
			m_pDataSet.reset();
		}
		m_pDataSet = pDataSet;
	}
	const math::Matrix44& VoxelWorldImpl::GetWorldTransform()
	{
		return m_pObject->GetWorldTransform();
	}
	Contact VoxelWorldImpl::Intersect(const math::Ray& r)
	{
		math::Matrix44 worldMatrix = m_pObject->GetWorldTransform();

		math::Matrix44 invWorld = worldMatrix;
		invWorld.Invert();

		

		math::Ray local_r = r;
		math::TransformRay(local_r, invWorld);

		Contact ret;
		
		math::Vector3 pt;
		math::Vector3 normal;

		if(false == m_pDataSet->Intersect(local_r, pt, normal))
		{
			return ret;
		}
		ret.result = Contact::Yes;

		ret.enter_point = pt;
		math::TransformCoord(ret.enter_point, worldMatrix);

		ret.normal = normal;
		math::TransformNormal(ret.normal, worldMatrix);

		return ret;
	}
	Contact VoxelWorldImpl::Intersect(BoundPtr pBound)
	{
		switch(pBound->type)
		{
		case Bound::bt_aabb:
			return _intersect_aabb(pBound);
		default:
			assert(0);
			break;
		}


		return Contact();
	}
	Contact	VoxelWorldImpl::_intersect_aabb(const BoundPtr pBound)
	{
		Contact ret;

		math::Matrix44 inv = m_pObject->GetWorldTransform();
		inv.Invert();

		Bound_AABBPtr pAABB = std::dynamic_pointer_cast<Bound_AABB>(pBound);
		
		math::AABBox box = pAABB->aabb;

		math::TransformAABB(box, pAABB->worldMatrix * inv);

		math::AABBox overlap;
		
		if(false == m_pDataSet->Intersect(box, overlap))
		{
			return ret;
		}

		ret.result = Contact::Yes;

		const math::Vector3& box_center = box.GetCenter();
		const math::Vector3& overlap_center = overlap.GetCenter();
		const math::Vector3& overlap_extent = overlap.GetExtent();

		math::Vector3 sig = box_center - overlap_center;
		
		math::Vector3 offset(0, 0, 0);

		int i_min = -1;
		Real min_dst = math::MATH_REAL_INFINITY;

		for(int i = 0; i < 3; ++i)
		{
			if(overlap_extent[i] < min_dst)
			{
				min_dst = overlap_extent[i];
				i_min = i;
			}
		}

		ret.enter_point = overlap_center;
		ret.normal = math::Vector3(0, 0, 0);


		if(box_center[i_min] > overlap_center[i_min])
		{
			ret.enter_point[i_min] += overlap_extent[i_min] / 2.0f;
			ret.normal[i_min] = 1;
		}
		else
		{
			ret.enter_point[i_min] -= overlap_extent[i_min] / 2.0f;
			ret.normal[i_min] = -1;
		}
		
		math::TransformCoord(ret.enter_point, m_pObject->GetWorldTransform());
		math::TransformNormal(ret.normal, m_pObject->GetWorldTransform());

		return ret;
	}
}

