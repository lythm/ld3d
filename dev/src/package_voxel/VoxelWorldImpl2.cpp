#include "voxel_pch.h"
#include "VoxelWorldImpl2.h"
#include "VoxelWorldRendererImpl2.h"

namespace ld3d
{
	VoxelWorldImpl2::VoxelWorldImpl2(GameObjectManagerPtr pManager) : VoxelWorld(pManager)
	{
		m_voxelSize				= 1;
		m_worldSizeX			= 10;
		m_worldSizeY			= 2;
		m_worldSizeZ			= 10;
		
		SetVersion(g_packageVersion);
	}


	VoxelWorldImpl2::~VoxelWorldImpl2(void)
	{
	}
	const int& VoxelWorldImpl2::GetWorldSizeX()
	{
		return m_worldSizeX;
	}
	void VoxelWorldImpl2::SetWorldSizeX(const int& x)
	{
		m_worldSizeX = x;
	}

	const int& VoxelWorldImpl2::GetWorldSizeY()
	{
		return m_worldSizeY;
	}
	void VoxelWorldImpl2::SetWorldSizeY(const int& y)
	{
		m_worldSizeY = y;
	}

	const int& VoxelWorldImpl2::GetWorldSizeZ()
	{
		return m_worldSizeZ;
	}
	void VoxelWorldImpl2::SetWorldSizeZ(const int& z)
	{
		m_worldSizeZ = z;
	}
	const int& VoxelWorldImpl2::GetVoxelSize()
	{
		return m_voxelSize;
	}
	void VoxelWorldImpl2::SetVoxelSize(const int& blockSize)
	{
		m_voxelSize = blockSize;
	}
	bool VoxelWorldImpl2::CreateWorld(const std::string& name)
	{
		if(m_pWorld == nullptr)
		{
			m_pWorld = m_pManager->alloc_object<voxel::World>();
		}
		using namespace voxel;

		Meshizer::VoxelMaterial mat;
		mat.type = 1;
		mat.materials[0] = 0;
		mat.materials[1] = 0;
		mat.materials[2] = 0;
		mat.materials[3] = 0;
		mat.materials[4] = 0;
		mat.materials[5] = 0;
		
		

		m_pMeshizer = m_pManager->alloc_object<voxel::Meshizer>();

		m_pMeshizer->AddVoxelMaterial(1, mat);

		MaterialPtr pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/voxel/material/voxel_world.material");
		if(pMaterial == nullptr)
		{
			return false;
		}

		TexturePtr pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/dirt.dds");

		pMaterial->GetParameterByName("diffuse_map")->SetParameterTexture(pTex);

		m_materials.push_back(pMaterial);

		if(false == m_pWorld->Create(name, nullptr, m_pMeshizer, m_pManager->GetAllocator(), m_pManager->logger()))
		{
			return false;
		}

		ResetComponents(m_pWorld);

		return true;

	}
	void VoxelWorldImpl2::DestroyWorld()
	{
		if(m_pWorld == nullptr)
		{
			return;
		}

		ResetComponents(nullptr);

		m_pWorld->Destroy();
		m_pWorld = nullptr;

	}
	void VoxelWorldImpl2::Update(float dt)
	{
		if(m_pWorld)
		{
			m_pWorld->Update(dt);
		}
	}
	bool VoxelWorldImpl2::OnAttach()
	{
		RegisterProperty<int, VoxelWorldImpl2>(this,
				"Voxel Size",
				&VoxelWorldImpl2::GetVoxelSize,
				&VoxelWorldImpl2::SetVoxelSize);

		RegisterProperty<int, VoxelWorldImpl2>(this,
				"World Size X",
				&VoxelWorldImpl2::GetWorldSizeX,
				&VoxelWorldImpl2::SetWorldSizeX);

		RegisterProperty<int, VoxelWorldImpl2>(this,
				"World Size Y",
				&VoxelWorldImpl2::GetWorldSizeY,
				&VoxelWorldImpl2::SetWorldSizeY);

		RegisterProperty<int, VoxelWorldImpl2>(this,
				"World Size Z",
				&VoxelWorldImpl2::GetWorldSizeZ,
				&VoxelWorldImpl2::SetWorldSizeZ);

		CreateWorld("empty");

		m_hEndFrame = m_pManager->AddEventHandler(EV_END_FRAME, std::bind(&VoxelWorldImpl2::_on_end_frame, this, std::placeholders::_1));
		return true;
	}
	void VoxelWorldImpl2::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hEndFrame);
		ClearPropertySet();
		for(auto pMaterial : m_materials)
		{
			pMaterial->Release();
		}
		m_materials.clear();
		m_pMeshizer.reset();
		DestroyWorld();
	}
	voxel::WorldPtr VoxelWorldImpl2::GetWorld()
	{
		return m_pWorld;
	}
	void VoxelWorldImpl2::ResetComponents(voxel::WorldPtr pWorld)
	{
		std::shared_ptr<VoxelWorldRendererImpl2> pRenderer = std::dynamic_pointer_cast<VoxelWorldRendererImpl2>(m_pObject->GetComponent("VoxelWorldRenderer"));

		if(pRenderer != nullptr)
		{
			pRenderer->ResetWorld(pWorld, m_materials);
		}
	}
	void VoxelWorldImpl2::_on_end_frame(EventPtr pEvent)
	{
		if(m_pWorld)
		{
			m_pWorld->UpdateLoaderProcess();
		}
	}
	uint32 VoxelWorldImpl2::GetLoadingQueueSize()
	{
		if(m_pWorld == nullptr)
		{
			return 0;
		}

		return m_pWorld->GetLoadingQueueSize();
	}
	
	uint32 VoxelWorldImpl2::GetChunkCount()
	{
		if(m_pWorld == nullptr)
		{
			return 0;
		}

		return m_pWorld->GetChunkCount();
	}
	const std::vector<MaterialPtr>& VoxelWorldImpl2::GetMaterials()
	{
		return m_materials;
	}
}
