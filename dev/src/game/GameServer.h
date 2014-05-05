#pragma once


namespace server
{
	class GameServer
	{
	public:
		GameServer(void);
		virtual ~GameServer(void);

		bool										Initialize();
		void										Release();
		void										Run();
		void										RunFrame();

	};
}
