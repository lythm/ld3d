#include "voxel_pch.h"
#include "VoxelWorldMaterialManager.h"


namespace ld3d
{
	VoxelWorldMaterialManager::VoxelWorldMaterialManager(void)
	{
	}


	VoxelWorldMaterialManager::~VoxelWorldMaterialManager(void)
	{
	}
	bool VoxelWorldMaterialManager::Initialize(RenderManagerPtr pRenderManager)
	{
		MaterialParameterPtr		pParam;

		TexturePtr					pTex;
		MaterialPtr					pMat;


		// soil
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/dirt.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_SOIL].pTex		= pTex;
		m_materials[VT_SOIL].pMaterial	= pMat;

		// rock
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/rock.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_STONE].pTex		= pTex;
		m_materials[VT_STONE].pMaterial	= pMat;

		// iron
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/rock.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_IRON].pTex		= pTex;
		m_materials[VT_IRON].pMaterial	= pMat;


		// silver
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/rock.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_SILVER].pTex		= pTex;
		m_materials[VT_SILVER].pMaterial	= pMat;
					
					

		// gold
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/rock.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_GOLD].pTex		= pTex;
		m_materials[VT_GOLD].pMaterial	= pMat;

		// water
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/dirt.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_WATER].pTex		= pTex;
		m_materials[VT_WATER].pMaterial	= pMat;
							
					
		// grass
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/dirt.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_GRASS].pTex		= pTex;
		m_materials[VT_GRASS].pMaterial	= pMat;

		// sand
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/sand.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_BEACH].pTex		= pTex;
		m_materials[VT_BEACH].pMaterial	= pMat;

		// tree leaf
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/sand.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_TREE_LEAF].pTex		= pTex;
		m_materials[VT_TREE_LEAF].pMaterial	= pMat;


		// tree trunk
		pTex = pRenderManager->CreateTextureFromFile("assets/voxel/texture/sand.dds");
		pMat = pRenderManager->CreateMaterialFromFile("assets/voxel/material/voxel_world.material");

		pParam = pMat->GetParameterByName("diffuse_map");
		pParam->SetParameterTexture(pTex);

		m_materials[VT_TREE_TRUNK].pTex		= pTex;
		m_materials[VT_TREE_TRUNK].pMaterial	= pMat;

		return true;
	}
	void VoxelWorldMaterialManager::Release()
	{
		for(auto v : m_materials)
		{
			v.second.pMaterial->Release();
			v.second.pTex->Release();
		}

		m_materials.clear();
	}
	MaterialPtr VoxelWorldMaterialManager::GetMaterialByType(uint8 type)
	{
		return m_materials[type].pMaterial;
	}
}
