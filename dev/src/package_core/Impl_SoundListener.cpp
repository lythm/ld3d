#include "core_ext_pch.h"
#include "Impl_SoundListener.h"



namespace ld3d
{

	Impl_SoundListener::Impl_SoundListener(GameObjectManagerPtr pManager) : SoundListener(pManager)
	{
		SetVersion(g_packageVersion);
	}


	Impl_SoundListener::~Impl_SoundListener(void)
	{
	}
	void Impl_SoundListener::Update(float dt)
	{
		const math::Matrix44& mat = m_pObject->GetWorldTransform();
		
		Sys_SoundPtr pSoundSys = m_pManager->GetSysSound();

		pSoundSys->SetListenerAttr(mat.GetTranslation(), math::Vector3(), mat.GetRow3(2), mat.GetRow3(1));

	}
	bool Impl_SoundListener::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool Impl_SoundListener::OnUnSerialize(DataStream* pStream, const Version& version )
	{
		return true;
	}
	
	bool Impl_SoundListener::OnAttach()
	{
		
		return true;
	}
	void Impl_SoundListener::OnDetach()
	{
		ClearPropertySet();
	}
}
