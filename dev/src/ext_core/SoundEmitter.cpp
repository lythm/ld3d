#include "core_ext_pch.h"
#include "..\..\include\core\ext\SoundEmitter.h"



namespace ld3d
{

	SoundEmitter::SoundEmitter(GameObjectManagerPtr pManager):GameObjectComponent(L"SoundEmitter", pManager)
	{
		m_bStreamed = false;
	}


	SoundEmitter::~SoundEmitter(void)
	{
	}
	void SoundEmitter::Update()
	{
		if(m_pChannel)
		{
			math::Vector3 pos = m_pObject->GetWorldTransform().GetTranslation();
			m_pChannel->SetPosition(pos.x, pos.y, pos.z);
		}
	}
	bool SoundEmitter::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool SoundEmitter::OnUnSerialize(DataStream* pStream, const Version& version )
	{
		return true;
	}
	const Version& SoundEmitter::GetVersion() const
	{
		return g_packageVersion;
	}

	bool SoundEmitter::OnAttach()
	{
		boost::filesystem::path p = boost::filesystem::current_path();
		//m_pChannel = m_pManager->GetSysSound()->Create3DStream("./assets/standard/music/1.mp3");

		m_pSound = boost::shared_dynamic_cast<SoundAsset>(m_pManager->GetAssetManager()->LoadAsset("./assets/standard/music/1.mp3"));

		m_pChannel = m_pManager->GetSysSound()->AllocChannel(m_pSound->GetAsset());

		//m_pChannel = m_pManager->GetSysSound()->Create3DStream("http://music.k618.cn/tytq/song/201208/W020120827815517810655.mp3");

		m_pChannel->Play(true);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"SoundEmitter");
		{
			pPM->RegisterProperty<bool, SoundEmitter>(this,
					L"Streamed",
					&SoundEmitter::GetStreamed,
					&SoundEmitter::SetStreamed);

		}

		pPM->End();
		return true;
	}
	void SoundEmitter::OnDetach()
	{
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
	const bool& SoundEmitter::GetStreamed()
	{
		return m_bStreamed;
	}
	void SoundEmitter::SetStreamed(const bool& streamed)
	{
		m_bStreamed = streamed;
	}
}
