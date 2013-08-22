#include "core_pch.h"
#include "core/GameObjectTemplate.h"
#include "core/DataStream_Mem.h"
#include "core_utils.h"

namespace ld3d
{
	GameObjectTemplate::GameObjectTemplate(GameObjectManagerPtr pManager, const std::string& name, const std::string& catalog)
	{
		m_pManager = pManager;
		m_name = name;
		m_catalog = catalog;
	}


	GameObjectTemplate::~GameObjectTemplate(void)
	{
		m_pManager.reset();
	}
	const std::string& GameObjectTemplate::GetName()
	{
		return m_name;
	}
	void GameObjectTemplate::SetName(const std::string& name)
	{
		m_name = name;
	}
	void GameObjectTemplate::SetCataLog(const std::string& catalog)
	{
		m_catalog = catalog;
	}
	const std::string& GameObjectTemplate::GetCataLog()
	{
		return m_catalog;
	}
}
