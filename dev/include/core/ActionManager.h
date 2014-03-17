#pragma once

namespace ld3d
{
	class ActionManager
	{
	public:
		
		struct Action
		{
			std::string								name;
			uint32									key;
			uint32									action;
		};
		

		typedef std::map<uint32, Action>			ActionMap;


		ActionManager(void);
		virtual ~ActionManager(void);

		bool										RegisterAction(uint32 key, const std::string& name, uint32 action);
		void										ModifyAction(uint32 key, const std::string& name, uint32 action);
		bool										FindAction(uint32 key, Action& action);

		void										Clear();

	private:
		ActionMap									m_actionMap;
	};


}