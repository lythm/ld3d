#pragma once


#include "core/GameInterface.h"


namespace ld3d
{
	class GameManager
	{
		
		typedef GameInterface*					(*Fn_CreateGame)();
		typedef void							(*Fn_DestroyGame)(GameInterface*);

	public:
		GameManager(void);
		virtual ~GameManager(void);

		bool									Initialize(CoreApiPtr pCore, const std::string& name);
		void									Release();

		GameInterface*							GetGame();

		void									Update(float dt);

	private:
		
		
		void*									m_hLib;
		std::string								m_filename;
		GameInterface*							m_pGame;
	};


	typedef std::shared_ptr<GameManager>		GameManagerPtr;

}
