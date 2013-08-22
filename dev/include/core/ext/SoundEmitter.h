#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{

	class SoundEmitter : public GameObjectComponent
	{
	public:
		SoundEmitter(GameObjectManagerPtr pManager);
		virtual ~SoundEmitter(void);

		void										Update(float dt);
		
		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );
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