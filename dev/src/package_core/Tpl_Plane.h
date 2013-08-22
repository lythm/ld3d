#pragma once

namespace ld3d
{
	class Tpl_Plane : public GameObjectTemplate
	{
	public:
		Tpl_Plane(GameObjectManagerPtr pManager, const std::string& name);
		virtual ~Tpl_Plane(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}