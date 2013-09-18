#pragma once

namespace ld3d
{
	class ActionMapping
	{
	public:

		struct KeyMap
		{
			uint32						key;
			uint32						action;
		};
		ActionMapping(void);
		virtual ~ActionMapping(void);


	private:

	};


}