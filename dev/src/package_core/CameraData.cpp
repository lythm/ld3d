#include "core_ext_pch.h"
#include "core/ext/CameraData.h"

namespace ld3d
{
	CameraData::CameraData(GameObjectManagerPtr pManager) : GameObjectComponent(L"Camera", pManager)
	{
		SetVersion(g_packageVersion);
	}


	CameraData::~CameraData(void)
	{
	}
	
	bool CameraData::OnAttach()
	{
		m_pCamera = m_pManager->alloc_object<Camera>();

		float aspect = float(800) / float(600);
		m_pCamera->PerspectiveFovLH(1.0f/ 4.0f * math::MATH_PI, aspect, 0.1f, 10000);
		
		m_pManager->GetRenderManager()->AddCamera(m_pCamera);

		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		
		pPM->Begin(L"Camera");
		{
			pPM->RegisterProperty<int, Camera>(m_pCamera.get(),
									L"Rendering Order",
									&Camera::GetOrder,
									&Camera::SetOrder);

		}
		pPM->End();

		return true;
	}
	void CameraData::OnDetach()
	{
		m_pManager->GetRenderManager()->RemoveCamera(m_pCamera);
		m_pCamera.reset();
	}
	bool CameraData::OnSerialize(DataStream* pStream)
	{
		int order = m_pCamera->GetOrder();
		pStream->WriteInt32(order);
		return true;
	}
	bool CameraData::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != g_packageVersion)
		{
			return false;
		}
		int order = pStream->ReadInt32();
		m_pCamera->SetOrder(order);
		return true;
	}
	void CameraData::Update(float dt)
	{
		math::Matrix44 mat = m_pObject->GetWorldTransform();

		mat.Invert();

		m_pCamera->SetViewMatrix(mat);
	}
}
