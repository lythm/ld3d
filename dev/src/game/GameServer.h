#pragma once


namespace server
{
	class GameServer
	{
	public:
		GameServer(void);
		virtual ~GameServer(void);

		bool										Initialize(ld3d::Logger& logger);
		void										Release();
		void										Run();

		void										RunFrame();

	private:

		static ld3d::Logger							s_logger;
	};
}
