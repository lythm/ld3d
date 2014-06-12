#include "voxel_pch.h"
#include "VoxelWorldRendererImpl2.h"
#include "VoxelWorldImpl2.h"


namespace ld3d
{

	VoxelWorldRendererImpl2::VoxelWorldRendererImpl2(GameObjectManagerPtr pManager) : VoxelWorldRenderer(pManager)
	{
		m_bShowBound = false;

		m_bShowBound = false;
		SetVersion(g_packageVersion);
	}


	VoxelWorldRendererImpl2::~VoxelWorldRendererImpl2(void)
	{
	}
	const bool&	VoxelWorldRendererImpl2::GetShowBound()
	{
		return m_bShowBound;
	}
	void VoxelWorldRendererImpl2::SetShowBound(const bool& show)
	{
		m_bShowBound = show;
	}
	bool VoxelWorldRendererImpl2::OnAttach()
	{
		

		std::vector<std::string> files;
		files.push_back("./assets/voxel/texture/dirt.dds");
		files.push_back("./assets/voxel/texture/rock.dds");
		//files.push_back("./assets/voxel/texture/sand.dds");

		TexturePtr pTex = m_pManager->GetRenderManager()->Create2DTextureArrayFromFileList(files);


	//	TexturePtr pTex1 = m_pManager->GetRenderManager()->CreateTextureFromFile("./assets/voxel/texture/block.dds");


		RegisterProperty<bool, VoxelWorldRendererImpl2>(this,
				"Show Bound",
				&VoxelWorldRendererImpl2::GetShowBound,
				&VoxelWorldRendererImpl2::SetShowBound);
				
		
		m_pMeshizer = m_pManager->alloc_object<voxel::ChunkMeshizer>();

		std::shared_ptr<VoxelWorldImpl2> pWorld = std::dynamic_pointer_cast<VoxelWorldImpl2>(m_pObject->GetComponent("VoxelWorld"));
		if(pWorld != nullptr)
		{
			ResetWorld(pWorld->GetWorld());
		}

		
		return true;
	}
	void VoxelWorldRendererImpl2::OnDetach()
	{
		if(m_pWorldVP)
		{
			m_pWorldVP->Close();
			m_pWorldVP.reset();
		}
		m_pMeshizer.reset();
	
	}
	void VoxelWorldRendererImpl2::Update(float dt)
	{
		if(m_pViewPortRoot)
		{
			math::Vector3 pos = m_pViewPortRoot->GetWorldTransform().GetTranslation();
			m_pWorldVP->MoveTo(voxel::Coord(pos.x, pos.y, pos.z));
		}
		if(m_pWorldVP)
		{
			m_pWorldVP->Update();
		}
	}
	void VoxelWorldRendererImpl2::BindWorldViewPort(GameObjectPtr pNode)
	{
		m_pViewPortRoot = pNode;
	}
	void VoxelWorldRendererImpl2::MoveViewPortTo(uint32 x, uint32 y, uint32 z)
	{
		m_pWorldVP->MoveTo(voxel::Coord(x, y, z));
	}
	void VoxelWorldRendererImpl2::ResetWorld(voxel::WorldPtr pWorld)
	{
		if(m_pWorldVP)
		{
			m_pWorldVP->Close();
			m_pWorldVP.reset();
		}

		if(pWorld == nullptr)
		{
			return;
		}

		m_pWorldVP = m_pManager->alloc_object<voxel::WorldViewport>();

		if(false == m_pWorldVP->Open(pWorld, voxel::Coord(0, 0, 0), voxel::REGION_SIZE * 3, nullptr))
		{
			return;
		}

		const std::list<voxel::ChunkPtr>& dcl = m_pWorldVP->GetDirtyChunkList();

	}
}
