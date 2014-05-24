#include "utils_pch.h"
#include "utils/TaskManager.h"


namespace ld3d
{

	TaskManager::TaskManager(void)
	{
	}


	TaskManager::~TaskManager(void)
	{
	}
	TaskManager::TaskID TaskManager::AddTask(const Task& task)
	{
		m_taskList.push_back(task);
		TaskID id = m_taskList.end();
		id--;
		return id;
	}
	void TaskManager::RemoveTask(TaskID id)
	{
		m_taskList.erase(id);
	}
	void TaskManager::Update()
	{
		for(auto t : m_taskList)
		{
			t();
		}
	}
	void TaskManager::Clear()
	{
		m_taskList.clear();
	}
}
