#include "voxel_pch.h"
#include "VoxelWorldImpl.h"
#include "VoxelWorldChunk.h"
#include "VoxelWorldDataSet.h"
#include "VoxelWorldUtils.h"

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
}

