#include "core_ext_pch.h"
#include "Impl_CameraData.h"


namespace ld3d
{
	Impl_CameraData::Impl_CameraData(GameObjectManagerPtr pManager) : CameraData(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_CameraData::~Impl_CameraData(void)
	{
	}
	
	bool Impl_CameraData::OnAttach()
	{
		m_pCamera = m_pManager->alloc_object<Camera>();

		float aspect = float(800) / float(600);
		m_pCamera->PerspectiveFovLH(1.0f/ 4.0f * math::MATH_PI, aspect, 0.1f, 10000);
		
		m_pManager->GetRenderManager()->AddCamera(m_pCamera);

		RegisterProperty<int, Camera>(m_pCamera.get(),
									"Rendering Order",
									&Camera::GetOrder,
									&Camera::SetOrder);

		return true;
	}
	void Impl_CameraData::OnDetach()
	{
		ClearPropertySet();
		m_pManager->GetRenderManager()->RemoveCamera(m_pCamera);
		m_pCamera.reset();
	}
	bool Impl_CameraData::OnSerialize(DataStream* pStream)
	{
		int order = m_pCamera->GetOrder();
		pStream->WriteInt32(order);
		return true;
	}
	bool Impl_CameraData::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != g_packageVersion)
		{
			return false;
		}
		int order = pStream->ReadInt32();
		m_pCamera->SetOrder(order);
		return true;
	}
	void Impl_CameraData::Update(float dt)
	{
		math::Matrix44 mat = m_pObject->GetWorldTransform();

		mat.Invert();

		m_pCamera->SetViewMatrix(mat);
	}
	CameraPtr Impl_CameraData::GetCamera()
	{
		return m_pCamera;
	}
}
