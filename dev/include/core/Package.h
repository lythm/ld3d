#pragma once


namespace ld3d
{
	class GameObjectTemplate;

	class Package
	{
	public:

		struct ComponentClass
		{
			ComponentClass(const std::string& name, 
								const std::string& catalog, 
								const std::string& desc, 
								std::function<GameObjectComponentPtr (GameObjectManagerPtr)> creator,
								bool bExclusive = true)
			{
				m_name						= name;
				m_catalog					= catalog;
				m_desc						= desc;
				m_creator					= creator;
				m_bExclusive				= bExclusive;
			}
			ComponentClass()
			{

			}
		
			std::string									m_name;
			std::string									m_catalog;
			std::string									m_desc;
			std::function<GameObjectComponentPtr (GameObjectManagerPtr)>		m_creator;
			bool											m_bExclusive;
		};

		virtual const char*									GetPackageName()								= 0;
		virtual int											GetClassCount()									= 0;
		virtual ComponentClass*								GetClassByIndex(int index)						= 0;

		virtual int											GetTemplateCount(){return 0;}
		virtual GameObjectTemplate*							GetTemplateByIndex(int index){return nullptr;}

		virtual void										Release()										= 0;

	protected:
		Package(void){}
		virtual ~Package(void){}
	private:

	};

	template <typename T>
	inline GameObjectComponentPtr Create_Component(GameObjectManagerPtr pManager)
	{
#ifdef __APPLE__
        return std::make_shared<T>(pManager);
#else
		return pManager->alloc_object<T>(pManager);
#endif
	}
}
