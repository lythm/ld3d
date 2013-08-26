#pragma once

#include <boost/enable_shared_from_this.hpp>
namespace ld3d
{
	class _DLL_CLASS GameObjectComponent: public std::enable_shared_from_this<GameObjectComponent>
	{
	public:
		GameObjectComponent(const std::string& name, GameObjectManagerPtr pManager);
		GameObjectComponent(GameObjectManagerPtr pManager);
		virtual ~GameObjectComponent(void);
		
		virtual void												Update(float dt);

		virtual bool												Attach(GameObjectPtr pObject);
		virtual void												Detach();
		
		bool														Serialize(DataStream* pStream);
		bool														UnSerialize(DataStream* pStream);

		virtual bool												OnSerialize(DataStream* pStream);
		virtual bool												OnUnSerialize(DataStream* pStream, const Version& version);
		
		const std::string&											GetName();

		void														SetName(const std::string& name);

		GameObjectPtr												GetGameObject();

		GameObjectManagerPtr										GetGameObjectManager();

		const Version&												GetVersion() const;
		void														SetVersion(const Version& v);

		const wchar_t*												GetVersionString();

		virtual GameObjectComponentPtr Clone();

		bool														IsExclusive();
		void														SetExclusive(bool v);
		
	
	private:
		virtual bool												OnAttach();
		virtual void												OnDetach();
		
	protected:
		GameObjectPtr												m_pObject;
		std::string													m_name;
		GameObjectManagerPtr										m_pManager;
		bool														m_bExclusive;
		Version														m_version;
	};
}
