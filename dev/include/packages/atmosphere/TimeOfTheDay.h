#pragma once

namespace ld3d
{
	namespace atmosphere
	{
		class TimeOfTheDay: public GameObjectComponent
		{
		public:

			TimeOfTheDay(GameObjectManagerPtr pManager) : GameObjectComponent("Atmosphere.TimeOfTheDay", pManager){}
			

			virtual ~TimeOfTheDay(void){}
		};


	}
}
