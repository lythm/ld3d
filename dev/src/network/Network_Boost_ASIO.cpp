#include "network_pch.h"
#include "Network_Boost_ASIO.h"



namespace ld3d
{

	Logger											g_logger;
}

_DLL_API ld3d::Sys_Network* CreateSys(ld3d::Logger& logger)
{
	ld3d::g_logger = logger;
	return new ld3d::Network_Boost_ASIO;
}

_DLL_API void DestroySys(ld3d::Sys_Network* pSys)
{
	delete (ld3d::Network_Boost_ASIO*)pSys;
}


namespace ld3d
{
	Network_Boost_ASIO::Network_Boost_ASIO(void)
	{
	}


	Network_Boost_ASIO::~Network_Boost_ASIO(void)
	{
	}

	void Network_Boost_ASIO::Update()
	{

	}
	bool Network_Boost_ASIO::Initialize()
	{
		return true;
	}
	void Network_Boost_ASIO::Release()
	{

	}
}
