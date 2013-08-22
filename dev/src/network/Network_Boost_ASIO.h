#pragma once


#include "core/Sys_Network.h"


namespace ld3d
{
	class Network_Boost_ASIO : public Sys_Network
	{
	public:
		Network_Boost_ASIO(void);
		virtual ~Network_Boost_ASIO(void);


		bool										Initialize();
		void										Release();
		void										Update();

	};
}
