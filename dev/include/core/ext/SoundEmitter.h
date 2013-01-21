#pragma once

#include "core\GameObjectComponent.h"
namespace ld3d
{

	class SoundEmitter : public GameObjectComponent
	{
	public:
		SoundEmitter(GameObjectManagerPtr pManager);
		virtual ~SoundEmitter(void);

		void										Update();
		
		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );
		const Version&								GetVersion() const;

		const bool&									GetStreamed();
		void										SetStreamed(const bool& streamed);

	private:
		bool										OnAttach();
		void										OnDetach();


	private:
		SoundChannelPtr								m_pChannel;
		SoundAssetPtr								m_pSound;
		bool										m_bStreamed;
	};



}