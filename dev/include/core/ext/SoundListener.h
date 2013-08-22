#pragma once

#include "core/GameObjectComponent.h"
namespace ld3d
{

	class SoundListener : public GameObjectComponent
	{
	public:
		SoundListener(GameObjectManagerPtr pManager);
		virtual ~SoundListener(void);

		void										Update(float dt);
		
		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

	private:
		bool										OnAttach();
		void										OnDetach();
	};



}
