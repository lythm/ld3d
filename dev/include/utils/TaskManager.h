#pragma once

#include <list>

namespace ld3d
{
	class TaskManager
	{
	public:
		typedef std::function<void ()>					Task;
		typedef std::list<Task>::iterator				TaskID;
		TaskManager(void);
		virtual ~TaskManager(void);

		TaskID											AddTask(const Task& task);
		void											RemoveTask(TaskID id);
		void											Update();

		void											Clear();
	private:
		std::list<Task>									m_taskList;
	};


}