#pragma once

namespace ld3d
{
	class Tpl_Camera: public GameObjectTemplate
	{
	public:
		Tpl_Camera(GameObjectManagerPtr pManager, const std::string& name);
		virtual ~Tpl_Camera(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}