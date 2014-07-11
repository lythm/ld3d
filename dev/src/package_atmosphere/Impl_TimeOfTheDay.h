#pragma once

#include "atmosphere/TimeOfTheDay.h"

namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{
			class Impl_TimeOfTheDay : public TimeOfTheDay
			{
			public:
				Impl_TimeOfTheDay(GameObjectManagerPtr pManager);
				virtual ~Impl_TimeOfTheDay(void);


				bool												OnAttach();
				void												OnDetach();
			};


		}
	}
}