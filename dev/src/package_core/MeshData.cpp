#include "core_ext_pch.h"
#include "core/ext/MeshData.h"
#include "core/Mesh.h"
#include "core/ext/MeshRenderer.h"
#include "core/GameObject.h"
#include "core/ext/PropertyManager.h"
#include "core/MeshUtil.h"
#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"

#include "CorePackage.h"

namespace ld3d
{

	MeshData::MeshData(GameObjectManagerPtr pManager) : GameObjectComponent("MeshData", pManager)
	{
		m_pMesh = MeshPtr();
		SetVersion(g_packageVersion);
	}


	MeshData::~MeshData(void)
	{

	}
	
	void MeshData::Update(float dt)
	{
		if(m_pMesh)
		{
			m_pMesh->Update();
		}
	}
	void MeshData::OnDetach()
	{
		if(m_pMesh)
		{
			m_pMesh->Destroy();
		}

	}
	MeshPtr	MeshData::GetMesh()
	{
		return m_pMesh;
	}
	void MeshData::SetMesh(MeshPtr pMesh)
	{
		if(m_pMesh)
		{
			m_pMesh->Destroy();
			m_pMesh.reset();
		}
		m_pMesh = pMesh;

		ResetMeshRenderer();
	}
	void MeshData::ResetMeshRenderer()
	{
		if(m_pObject == NULL)
		{
			return;
		}
		MeshRendererPtr pMR = std::dynamic_pointer_cast<MeshRenderer>(m_pObject->GetComponent("MeshRenderer"));
		if(pMR)
		{
			pMR->Reset(std::dynamic_pointer_cast<MeshData>(shared_from_this()));
		}
	}
	bool MeshData::OnAttach()
	{
		ResetMeshRenderer();

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));
		pPM->Begin("MeshData");

		pPM->RegisterProperty<std::string, MeshData>(this,
			"MeshAsset", 
			&MeshData::GetMeshAsset,
			&MeshData::SetMeshAsset);

		pPM->End();

		return true;
	}
	bool MeshData::SetMeshAsset(const std::string& asset)
	{
		m_meshAsset = asset;
	
		if(m_pMesh != nullptr)
		{
			m_pMesh->Destroy();	
		}

		if(m_meshAsset == "_cube_")
		{
			MaterialPtr pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/editor_shape.material");
			
			if(pMaterial == nullptr)
			{
				return false;
			}
			MeshPtr pMesh = MeshUtil::CreateCube(1, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else if(m_meshAsset == "_sphere_")
		{
			MaterialPtr pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/editor_shape.material");
			if(pMaterial == nullptr)
			{
				return false;
			}
			MeshPtr pMesh = MeshUtil::CreateSphere(1, 50, 50, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else if(m_meshAsset == "_cone_")
		{
			
			MaterialPtr pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/editor_shape.material");
			if(pMaterial == nullptr)
			{
				return false;
			}
			MeshPtr pMesh = MeshUtil::CreateCone(1, 30, 50, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else if(m_meshAsset == "_plane_")
		{
						
			MaterialPtr pMaterial = m_pManager->GetRenderManager()->CreateMaterialFromFile("./assets/standard/material/editor_shape.material");
			if(pMaterial == nullptr)
			{
				return false;
			}
			MeshPtr pMesh = MeshUtil::CreatePlane(100, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else
		{
			// load mesh assets
			LoadMesh(m_meshAsset);
		}

		return true;
	}
	const std::string& MeshData::GetMeshAsset()
	{
		return m_meshAsset;
	}

	bool MeshData::LoadMesh(const std::string& asset)
	{
		return true;
	}

	bool MeshData::OnSerialize(DataStream* pStream)
	{
		pStream->WriteString(m_meshAsset);
		return true;
	}
	bool MeshData::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}
		pStream->ReadString(m_meshAsset);

		SetMeshAsset(m_meshAsset);

		return true;
	}
}
