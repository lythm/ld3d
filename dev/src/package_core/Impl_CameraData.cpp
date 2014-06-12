#include "core_ext_pch.h"
#include "Impl_CameraData.h"


namespace ld3d
{
	Impl_CameraData::Impl_CameraData(GameObjectManagerPtr pManager) : CameraData(pManager)
	{
		SetVersion(g_packageVersion);

		m_np				= 0.1f;
		m_fp				= 1000.0f;
		m_aspect			= 4.0f/3.0f;
		m_fov				= 0.25f * math::MATH_PI;
	}


	Impl_CameraData::~Impl_CameraData(void)
	{
	}
	
	bool Impl_CameraData::OnAttach()
	{
		m_pCamera = m_pManager->alloc_object<Camera>();

		int w = m_pManager->GetCoreApi()->GetScreen()->GetFramebufferWidth();
		int h = m_pManager->GetCoreApi()->GetScreen()->GetFramebufferHeight();

		m_aspect = float(w) / float(h);
		m_pCamera->PerspectiveFovLH(m_fov, m_aspect, m_np, m_fp);
		
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
		UpdateCamera();
	}
	void Impl_CameraData::UpdateCamera()
	{
		math::Matrix44 mat = m_pObject->GetWorldTransform();

		mat.Invert();

		m_pCamera->SetViewMatrix(mat);
	}
	CameraPtr Impl_CameraData::GetCamera()
	{
		return m_pCamera;
	}
	void Impl_CameraData::SetViewport(const math::RectI& vp)
	{
		if(m_pCamera)
		{
			m_pCamera->SetViewport(vp);
		}
	}
	void Impl_CameraData::SetNearPlane(float np)
	{
		m_np = np;
		m_pCamera->PerspectiveFovLH(m_fov, m_aspect, m_np, m_fp);
	}
	void Impl_CameraData::SetFarPlane(float fp)
	{
		m_fp = fp;
		m_pCamera->PerspectiveFovLH(m_fov, m_aspect, m_np, m_fp);
	}
	void Impl_CameraData::SetAspect(float aspect)
	{
		m_aspect = aspect;
		m_pCamera->PerspectiveFovLH(m_fov, m_aspect, m_np, m_fp);
	}
	void Impl_CameraData::SetFOV(float fov)
	{
		m_fov = fov;
		m_pCamera->PerspectiveFovLH(m_fov, m_aspect, m_np, m_fp);
	}
}
