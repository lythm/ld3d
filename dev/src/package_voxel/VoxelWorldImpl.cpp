#include "voxel_pch.h"
#include "VoxelWorldImpl.h"
#include "VoxelWorldRendererImpl.h"

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
	const int& VoxelWorldImpl::GetVoxelSize()
	{
		return m_voxelSize;
	}
	void VoxelWorldImpl::SetVoxelSize(const int& blockSize)
	{
		m_voxelSize = blockSize;
	}
	bool VoxelWorldImpl::CreateWorld(const std::string& name)
	{
		if(m_pWorld == nullptr)
		{
			m_pWorld = m_pManager->alloc_object<voxel::World>();
		}
		using namespace voxel;

		

		m_pMeshizer = m_pManager->alloc_object<voxel::Meshizer>();

		Meshizer::VoxelMaterial mat;
		mat.type = 1;
		mat.materials[0] = 0;
		mat.materials[1] = 0;
		mat.materials[2] = 0;
		mat.materials[3] = 0;
		mat.materials[4] = 0;
		mat.materials[5] = 0;
		
		m_pMeshizer->AddVoxelMaterial(mat.type, mat);

		mat.type = 2;
		mat.materials[0] = 1;
		mat.materials[1] = 1;
		mat.materials[2] = 1;
		mat.materials[3] = 1;
		mat.materials[4] = 1;
		mat.materials[5] = 1;
		m_pMeshizer->AddVoxelMaterial(mat.type, mat);

		mat.type = 3;
		mat.materials[0] = 2;
		mat.materials[1] = 2;
		mat.materials[2] = 2;
		mat.materials[3] = 2;
		mat.materials[4] = 2;
		mat.materials[5] = 2;
		m_pMeshizer->AddVoxelMaterial(mat.type, mat);

		mat.type = 4;
		mat.materials[0] = 3;
		mat.materials[1] = 3;
		mat.materials[2] = 3;
		mat.materials[3] = 3;
		mat.materials[4] = 3;
		mat.materials[5] = 3;
		m_pMeshizer->AddVoxelMaterial(mat.type, mat);

		mat.type = 5;
		mat.materials[0] = 4;
		mat.materials[1] = 4;
		mat.materials[2] = 4;
		mat.materials[3] = 4;
		mat.materials[4] = 4;
		mat.materials[5] = 4;
		m_pMeshizer->AddVoxelMaterial(mat.type, mat);
		

		MaterialPtr pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/voxel/material/voxel_world.material");
		if(pMaterial == nullptr)
		{
			return false;
		}

		TexturePtr pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/dirt.dds");

		pMaterial->GetParameterByName("diffuse_map")->SetParameterTexture(pTex);

		m_materials.push_back(pMaterial);


		pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/voxel/material/voxel_world.material");
		pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/rock.dds");

		pMaterial->GetParameterByName("diffuse_map")->SetParameterTexture(pTex);
		m_materials.push_back(pMaterial);

		pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/voxel/material/voxel_world.material");
		pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/metal.dds");

		pMaterial->GetParameterByName("diffuse_map")->SetParameterTexture(pTex);
		m_materials.push_back(pMaterial);

		pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/voxel/material/voxel_world.material");
		pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/grass.dds");

		pMaterial->GetParameterByName("diffuse_map")->SetParameterTexture(pTex);
		m_materials.push_back(pMaterial);

		pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/voxel/material/voxel_world.material");
		pTex = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/sand.dds");

		pMaterial->GetParameterByName("diffuse_map")->SetParameterTexture(pTex);
		m_materials.push_back(pMaterial);


		pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/simple_line.material");
		m_materials.push_back(pMaterial);

		if(false == m_pWorld->Create(name, nullptr, m_pMeshizer, m_pManager->GetAllocator(), m_pManager->logger()))
		{
			return false;
		}

		ResetComponents(m_pWorld);

		return true;

	}
	void VoxelWorldImpl::DestroyWorld()
	{
		if(m_pWorld == nullptr)
		{
			return;
		}

		ResetComponents(nullptr);

		m_pWorld->Destroy();
		m_pWorld = nullptr;

	}
	void VoxelWorldImpl::Update(float dt)
	{
		if(m_pWorld)
		{
			m_pWorld->Update(dt);
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

		CreateWorld("empty");

		m_hEndFrame = m_pManager->AddEventHandler(EV_END_FRAME, std::bind(&VoxelWorldImpl::_on_end_frame, this, std::placeholders::_1));
		return true;
	}
	void VoxelWorldImpl::OnDetach()
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
	voxel::WorldPtr VoxelWorldImpl::GetWorld()
	{
		return m_pWorld;
	}
	void VoxelWorldImpl::ResetComponents(voxel::WorldPtr pWorld)
	{
		std::shared_ptr<VoxelWorldRendererImpl> pRenderer = std::dynamic_pointer_cast<VoxelWorldRendererImpl>(m_pObject->GetComponent("Voxel.WorldRenderer"));

		if(pRenderer != nullptr)
		{
			pRenderer->ResetWorld(pWorld, m_materials);
		}
	}
	void VoxelWorldImpl::_on_end_frame(EventPtr pEvent)
	{
		if(m_pWorld)
		{
			m_pWorld->UpdateLoaderProcess();
		}
	}
	uint32 VoxelWorldImpl::GetLoadingQueueSize()
	{
		if(m_pWorld == nullptr)
		{
			return 0;
		}

		return m_pWorld->GetLoadingQueueSize();
	}
	
	uint32 VoxelWorldImpl::GetChunkCount()
	{
		if(m_pWorld == nullptr)
		{
			return 0;
		}

		return m_pWorld->GetChunkCount();
	}
	int32 VoxelWorldImpl::GetNonEmptyChunkCount()
	{
		if(m_pWorld == nullptr)
		{
			return 0;
		}

		return m_pWorld->GetNonEmptyChunk();
	}
	const std::vector<MaterialPtr>& VoxelWorldImpl::GetMaterials()
	{
		return m_materials;
	}
	int32 VoxelWorldImpl::GetFaceCount()
	{
		if(m_pWorld == nullptr)
		{
			return 0;
		}

		return m_pWorld->GetTotalFaceCount();
	}
}
