#include "pch.h"
#include "GameManager.h"


namespace ld3d
{
	GameManager::GameManager(void)
	{
		m_hLib				= NULL;
		m_pGame				= NULL;
	}


	GameManager::~GameManager(void)
	{
	}
	bool GameManager::Initialize(const std::string& file)
	{
		m_hLib = os_load_module(file.c_str());

		if(m_hLib == NULL)
		{
			return false;
		}

		Fn_CreateGame CreateGame = (Fn_CreateGame)os_find_proc(m_hLib, "CreateGame");

		if(CreateGame == NULL)
		{
			return false;
		}
		m_filename = file;

		m_pGame = CreateGame();

		if(m_pGame == NULL)
		{
			return false;
		}
		return true;
	}
	void GameManager::Release()
	{
		if(m_hLib == NULL)
		{
			return;
		}
		Fn_DestroyGame DestroyGame = (Fn_DestroyGame)os_find_proc(m_hLib, "DestroyGame");

		if(DestroyGame != NULL)
		{
			DestroyGame(m_pGame);
		}


		os_unload_module(m_hLib);
		m_hLib = NULL;
	}

	GameInterface* GameManager::GetGame()
	{
		return m_pGame;
	}
}