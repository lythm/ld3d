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

		virtual GameObjectComponentPtr								Clone();

		bool														IsExclusive();
		void														SetExclusive(bool v);
		
	
		PropertySetPtr												GetPropertySet();
		void														ClearPropertySet();

		template<typename T>
		bool														RegisterProperty(const std::string& name, 
																		boost::function<const T& ()> getter,
																		boost::function<void (const T&)> setter = boost::function<void (const T&)>())
		{
			std::shared_ptr<Property_T<T> > pProp = CoreApi::GetAllocator()->AllocObject<Property_T<T> >(name);
			pProp->setType(PropTypeId<T>::m_type);
			pProp->m_getter = getter;
			pProp->m_setter = setter;

			m_pPropertySet->addProperty(pProp);

			return true;
		}

		template<typename T, typename TObject>
		bool														RegisterProperty(TObject* pObj, 
																		const std::string& name, 
																		boost::function<const T& (TObject*)> getter,
																		boost::function<void (TObject*, const T&)> setter =  boost::function<void (TObject*, const T&)>())
		{
			std::shared_ptr<Property_T<T> > pProp = m_pManager->alloc_object<Property_T<T> >(name);
			pProp->setType(PropTypeId<T>::m_type);
			pProp->m_getter = boost::bind(getter, pObj);

			if(setter)
			{
				pProp->m_setter = boost::bind(setter, pObj, _1);
			}
			else
			{
				pProp->m_setter = boost::function<void (const T&)>();
			}

			m_pPropertySet->addProperty(pProp);

			return true;
		}
	private:
		virtual bool												OnAttach();
		virtual void												OnDetach();
		
	protected:
		GameObjectPtr												m_pObject;
		std::string													m_name;
		GameObjectManagerPtr										m_pManager;
		bool														m_bExclusive;
		Version														m_version;

		PropertySetPtr												m_pPropertySet;
	};
}
