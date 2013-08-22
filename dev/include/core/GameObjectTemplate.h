#pragma once

namespace ld3d
{
	class EXPORT_CLASS GameObjectTemplate
	{
	public:
		GameObjectTemplate(GameObjectManagerPtr pManager, const std::string& name, const std::string& catalog = std::string("Misc"));
		virtual ~GameObjectTemplate(void);

		const std::string&						GetName();
		const std::string&						GetCataLog();

		void									SetName(const std::string& name);
		void									SetCataLog(const std::string& catalog);

		virtual GameObjectPtr					CreateGameObject()						= 0;
		virtual void							Release()								= 0;
	protected:

		GameObjectManagerPtr					m_pManager;
		std::string							m_name;
		std::string							m_catalog;
	};
}
