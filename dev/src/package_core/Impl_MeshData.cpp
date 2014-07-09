#include "core_ext_pch.h"
#include "Impl_MeshData.h"

#include "Impl_MeshRenderer.h"
#include "core/Mesh.h"

#include "core/GameObject.h"
#include "core/MeshUtil.h"
#include "core/RenderManager.h"
#include "core/Sys_Graphics.h"

#include "CorePackage.h"

namespace ld3d
{

	Impl_MeshData::Impl_MeshData(GameObjectManagerPtr pManager) : MeshData(pManager)
	{
		m_pMesh = MeshPtr();
		SetVersion(g_packageVersion);
	}


	Impl_MeshData::~Impl_MeshData(void)
	{

	}
	
	void Impl_MeshData::Update(float dt)
	{
		if(m_pMesh)
		{
			m_pMesh->Update();
		}
	}
	void Impl_MeshData::OnDetach()
	{
		ClearPropertySet();
		if(m_pMesh)
		{
			m_pMesh->Destroy();
		}

	}
	MeshPtr	Impl_MeshData::GetMesh()
	{
		return m_pMesh;
	}
	void Impl_MeshData::SetMesh(MeshPtr pMesh)
	{
		if(m_pMesh)
		{
			m_pMesh->Destroy();
			m_pMesh.reset();
		}
		m_pMesh = pMesh;

		ResetMeshRenderer();
	}
	void Impl_MeshData::ResetMeshRenderer()
	{
		if(m_pObject == NULL)
		{
			return;
		}
		std::shared_ptr<Impl_MeshRenderer> pMR = std::dynamic_pointer_cast<Impl_MeshRenderer>(m_pObject->GetComponent("MeshRenderer"));
		if(pMR)
		{
			pMR->Reset(std::dynamic_pointer_cast<Impl_MeshData>(shared_from_this()));
		}
	}
	bool Impl_MeshData::OnAttach()
	{
		ResetMeshRenderer();

		
		RegisterProperty<std::string, Impl_MeshData>(this,
			"MeshAsset", 
			&Impl_MeshData::GetMeshAsset,
			&Impl_MeshData::SetMeshAsset);

		

		return true;
	}
	bool Impl_MeshData::SetMeshAsset(const std::string& asset)
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
			//MeshPtr pMesh = MeshUtil::CreateSphere(1, 50, 50, pMaterial);
			MeshPtr pMesh = MeshUtil::CreateIcoSphere(50, 4, pMaterial);
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
	const std::string& Impl_MeshData::GetMeshAsset()
	{
		return m_meshAsset;
	}

	bool Impl_MeshData::LoadMesh(const std::string& asset)
	{
		return true;
	}

	bool Impl_MeshData::OnSerialize(DataStream* pStream)
	{
		pStream->WriteString(m_meshAsset);
		return true;
	}
	bool Impl_MeshData::OnUnSerialize(DataStream* pStream, const Version& version)
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

