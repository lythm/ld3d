#include "core_ext_pch.h"
#include "Impl_SoundEmitter.h"


namespace ld3d
{

	Impl_SoundEmitter::Impl_SoundEmitter(GameObjectManagerPtr pManager):SoundEmitter(pManager)
	{
		m_bStreamed = false;
		SetVersion(g_packageVersion);
	}


	Impl_SoundEmitter::~Impl_SoundEmitter(void)
	{
	}
	void Impl_SoundEmitter::Update(float dt)
	{
		if(m_pChannel)
		{
			math::Vector3 pos = m_pObject->GetWorldTransform().GetTranslation();
			m_pChannel->SetPosition(pos.x, pos.y, pos.z);
		}
	}
	bool Impl_SoundEmitter::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool Impl_SoundEmitter::OnUnSerialize(DataStream* pStream, const Version& version )
	{
		return true;
	}
	
	bool Impl_SoundEmitter::OnAttach()
	{
		boost::filesystem::path p = boost::filesystem::current_path();
		//m_pChannel = m_pManager->GetSysSound()->Create3DStream("./assets/standard/music/1.mp3");

		m_pSound = std::dynamic_pointer_cast<SoundAsset>(m_pManager->GetAssetManager()->LoadAsset("./assets/standard/music/1.mp3"));

		m_pChannel = m_pManager->GetSysSound()->AllocChannel(m_pSound->Value());

		//m_pChannel = m_pManager->GetSysSound()->Create3DStream("http://music.k618.cn/tytq/song/201208/W020120827815517810655.mp3");

		m_pChannel->Play(true);

	
		RegisterProperty<bool, SoundEmitter>(this,
					"Streamed",
					&SoundEmitter::GetStreamed,
					&SoundEmitter::SetStreamed);

		
		return true;
	}
	void Impl_SoundEmitter::OnDetach()
	{
		ClearPropertySet();
		if(m_pChannel)
		{
			m_pChannel->Release();
			m_pChannel.reset();
		}
		if(m_pSound)
		{
			m_pSound->Release();
			m_pSound.reset();
		}
	}
	const bool& Impl_SoundEmitter::GetStreamed()
	{
		return m_bStreamed;
	}
	void Impl_SoundEmitter::SetStreamed(const bool& streamed)
	{
		m_bStreamed = streamed;
	}
}
