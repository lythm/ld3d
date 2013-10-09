#pragma once

#include "packages/core/SoundEmitter.h"

namespace ld3d
{

	class Impl_SoundEmitter : public SoundEmitter
	{
	public:
		Impl_SoundEmitter(GameObjectManagerPtr pManager);
		virtual ~Impl_SoundEmitter(void);

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