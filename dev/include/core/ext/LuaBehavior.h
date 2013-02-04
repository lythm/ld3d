#pragma once

namespace ld3d
{
	class LuaBehavior : public GameObjectComponent
	{
	public:
		LuaBehavior(GameObjectManagerPtr pManager);
		virtual ~LuaBehavior(void);

		void						Update(float dt);
		const Version&				GetVersion() const;
	private:
		bool						OnAttach();
		void						OnDetach();
	private:

	};


}