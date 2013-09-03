#include "core_ext_pch.h"
#include "core/ext/SkyBox.h"


namespace ld3d
{
	SkyBox::SkyBox(GameObjectManagerPtr pManager) : GameObjectComponent("SkyBox", pManager)
	{
		SetVersion(g_packageVersion);
	}


	SkyBox::~SkyBox(void)
	{
	}
	void SkyBox::Update(float dt)
	{
	}
	
	bool SkyBox::OnAttach()
	{
	
		


		m_hFrustumCull = m_pManager->AddEventHandler(EV_FRUSTUM_CULL, boost::bind(&SkyBox::on_event_frustum_cull, this, _1));

		return true;
	}
	void SkyBox::OnDetach()
	{
		m_pManager->RemoveEventHandler(m_hFrustumCull);
	}
	void SkyBox::on_event_frustum_cull(EventPtr pEvent)
	{

	}
}
