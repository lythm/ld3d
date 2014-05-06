#pragma once

namespace client
{
	class GameClient
	{
	public:
		GameClient(void);
		virtual ~GameClient(void);

		bool								Initialize();
		void								Release();
		void								UpdateFrame();
	};


}
