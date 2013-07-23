#pragma once

namespace ld3d
{
	class GameObjectTemplate;

	class Package
	{
	public:

		struct ComponentClass
		{
			ComponentClass(const std::wstring& name, 
								const std::wstring& catalog, 
								const std::wstring& desc, 
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
		
			std::wstring									m_name;
			std::wstring									m_catalog;
			std::wstring									m_desc;
			std::function<GameObjectComponentPtr (GameObjectManagerPtr)>		m_creator;
			bool											m_bExclusive;
		};

		virtual const wchar_t*								GetPackageName()								= 0;
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
		return pManager->alloc_object<T>(pManager);
	}
}
