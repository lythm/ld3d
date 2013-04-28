#pragma once

#include "core\Sys_Network.h"

namespace ld3d
{
	class Network_Epoll : public Sys_Network
	{
	public:
		Network_Epoll(void);
		virtual ~Network_Epoll(void);
	};


}