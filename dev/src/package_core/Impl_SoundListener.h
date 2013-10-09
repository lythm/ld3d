#pragma once

#include "packages/core/SoundListener.h"

namespace ld3d
{

	class Impl_SoundListener : public SoundListener
	{
	public:
		Impl_SoundListener(GameObjectManagerPtr pManager);
		virtual ~Impl_SoundListener(void);

		void										Update(float dt);
		
		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	};



}
