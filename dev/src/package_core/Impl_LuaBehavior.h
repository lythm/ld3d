#pragma once

#include "packages/core/LuaBehavior.h"

namespace ld3d
{
	class Impl_LuaBehavior : public LuaBehavior
	{
	public:
		Impl_LuaBehavior(GameObjectManagerPtr pManager);
		virtual ~Impl_LuaBehavior(void);

		void						Update(float dt);

	private:
		bool						OnAttach();
		void						OnDetach();
	private:

	};


}