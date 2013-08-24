#include "core_ext_pch.h"
#include "core/ext/SoundListener.h"

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
		PropertyManagerPtr pPM = std::dynamic_pointer_cast<PropertyManager>(m_pObject->GetComponent("PropertyManager"));

		pPM->Begin("SoundListener");
		{
		}
		pPM->End();
		return true;
	}
	void SoundListener::OnDetach()
	{
	}
}