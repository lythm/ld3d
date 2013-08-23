#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class _DLL_CLASS Behavior : public GameObjectComponent
	{
	public:
		Behavior(GameObjectManagerPtr pManager);
		virtual ~Behavior(void);


		void						Update(float dt);
		bool						OnAttach();
		void						OnDetach();

	};
}
