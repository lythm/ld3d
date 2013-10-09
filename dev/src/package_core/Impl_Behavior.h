#pragma once

#include "packages/core/Behavior.h"

namespace ld3d
{
	class Impl_Behavior : public Behavior
	{
	public:
		Impl_Behavior(GameObjectManagerPtr pManager);
		virtual ~Impl_Behavior(void);

		
		void						Update(float dt);
		bool						OnAttach();
		void						OnDetach();

	};
}
