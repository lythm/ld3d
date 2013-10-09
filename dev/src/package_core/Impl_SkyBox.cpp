#include "core_ext_pch.h"
#include "Impl_SkyBox.h"



namespace ld3d
{
	Impl_SkyBox::Impl_SkyBox(GameObjectManagerPtr pManager) : SkyBox(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_SkyBox::~Impl_SkyBox(void)
	{
	}
	void Impl_SkyBox::Update(float dt)
	{
	}
	
	bool Impl_SkyBox::OnAttach()
	{
	
		


		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&Impl_SkyBox::on_event_frustum_cull, this, _1));

		return true;
	}
	void Impl_SkyBox::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);
	}
	void Impl_SkyBox::on_event_frustum_cull(EventPtr pEvent)
	{

	}
}
