#pragma once

namespace ld3d
{
	class Tpl_Cube : public GameObjectTemplate
	{
	public:
		Tpl_Cube(GameObjectManagerPtr pManager, const std::string& name);
		virtual ~Tpl_Cube(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}