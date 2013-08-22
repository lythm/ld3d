#pragma once

namespace ld3d
{
	class Tpl_SpotLight : public GameObjectTemplate
	{
	public:
		Tpl_SpotLight(GameObjectManagerPtr pManager, const std::string& name);
		virtual ~Tpl_SpotLight(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}