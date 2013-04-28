#pragma once
#include "core\Sys_Network.h"
namespace ld3d
{
	class Network_IOCP : public Sys_Network
	{
	public:
		Network_IOCP(void);
		virtual ~Network_IOCP(void);
	};

}