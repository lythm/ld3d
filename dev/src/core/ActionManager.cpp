#include "core_pch.h"
#include "core/ActionManager.h"

namespace ld3d
{
	ActionManager::ActionManager(void)
	{
	}


	ActionManager::~ActionManager(void)
	{
	}
	bool ActionManager::RegisterAction(uint32 key, const std::string& name, uint32 action)
	{
		if(m_actionMap.find(key) != m_actionMap.end())
		{
			return false;
		}
		m_actionMap[key].action			= action;
		m_actionMap[key].name			= name;
		m_actionMap[key].key			= key;

		return true;
	}
	void ActionManager::ModifyAction(uint32 key, const std::string& name, uint32 action)
	{
		Action find;
		if(false == FindAction(key, find))
		{
			return;
		}

		find.action = action;
		find.name = name;
	}
	bool ActionManager::FindAction(uint32 key, Action& action)
	{
		ActionMap::iterator it = m_actionMap.find(key);
		if(it == m_actionMap.end())
		{
			return false;
		}
		action = it->second;
		return true;
	}
	void ActionManager::Clear()
	{
		m_actionMap.clear();
	}
}