#include "core_ext_pch.h"
#include "packages/core/SoundListener.h"

namespace ld3d
{

	SoundListener::SoundListener(GameObjectManagerPtr pManager) : GameObjectComponent("SoundListener", pManager)
	{
		SetVersion(g_packageVersion);
	}


	SoundListener::~SoundListener(void)
	{
	}
	void SoundListener::Update(float dt)
	{
		const math::Matrix44& mat = m_pObject->GetWorldTransform();
		
		Sys_SoundPtr pSoundSys = m_pManager->GetSysSound();

		pSoundSys->SetListenerAttr(mat.GetTranslation(), math::Vector3(), mat.GetRow3(2), mat.GetRow3(1));

	}
	bool SoundListener::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool SoundListener::OnUnSerialize(DataStream* pStream, const Version& version )
	{
		return true;
	}
	
	bool SoundListener::OnAttach()
	{
		
		return true;
	}
	void SoundListener::OnDetach()
	{
		ClearPropertySet();
	}
}
