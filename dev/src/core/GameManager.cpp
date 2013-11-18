#include "core_pch.h"
#include "GameManager.h"


namespace ld3d
{
	GameManager::GameManager(void)
	{
		m_hLib				= nullptr;
		m_pGame				= nullptr;
	}


	GameManager::~GameManager(void)
	{
	}
	bool GameManager::Initialize(CoreApiPtr pCore, const std::string& name)
	{
		Release();

		using namespace boost::filesystem;

		path p = "./mods" / name;


		m_hLib = os_load_module(p.string().c_str());

		if(m_hLib == nullptr)
		{
			return false;
		}

		Fn_CreateGame CreateGame = (Fn_CreateGame)os_find_proc(m_hLib, "CreateGame");

		if(CreateGame == nullptr)
		{
			return false;
		}
		m_filename = p.string();

		m_pGame = CreateGame();

		if(m_pGame == NULL)
		{
			return false;
		}

		if(false == m_pGame->Initialize(pCore))
		{
			return false;
		}
		return true;
	}
	void GameManager::Release()
	{
		if(m_hLib == nullptr)
		{
			return;
		}

		if(m_pGame)
		{
			m_pGame->Release();
		}
		Fn_DestroyGame DestroyGame = (Fn_DestroyGame)os_find_proc(m_hLib, "DestroyGame");

		if(DestroyGame != nullptr)
		{
			DestroyGame(m_pGame);
		}


		os_unload_module(m_hLib);
		m_hLib = nullptr;
	}

	GameInterface* GameManager::GetGame()
	{
		return m_pGame;
	}
	void GameManager::Update(float dt)
	{
		if(m_pGame)
		{
			m_pGame->Update(dt);
		}
	}
}