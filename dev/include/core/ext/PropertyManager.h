#pragma once

#include "core/GameObjectComponent.h"
#include "core/allocator.h"
#include "core/coreapi.h"

#include <boost/function.hpp>

namespace ld3d
{

	class _DLL_CLASS PropertyManager : public GameObjectComponent
	{
	public:

		PropertyManager(GameObjectManagerPtr pManager);
		virtual ~PropertyManager(void);

		PropertySetPtr						Begin(const std::string& name);
		PropertySetPtr						FindPropertySet(const std::string& name);
		void								AddProperty(std::shared_ptr<Property> pProp);
		void								End();

		bool								OnAttach();
		void								OnDetach();
		int									GetPropertySetCount();
		PropertySetPtr						GetPropertySet(int index);

		void								ClearPropertySet(const std::string & name);

		Property*							FindProperty(const std::string& set, const std::string& name);

		template<typename T>
		bool								RegisterProperty(const std::string& name, 
			boost::function<const T& ()> getter,
			boost::function<void (const T&)> setter = boost::function<void (const T&)>())
		{
			std::shared_ptr<Property_T<T> > pProp = CoreApi::GetAllocator()->AllocObject<Property_T<T> >(name);
			pProp->setType(PropTypeId<T>::m_type);
			pProp->m_getter = getter;
			pProp->m_setter = setter;

			AddProperty(pProp);

			return true;
		}

		template<typename T, typename TObject>
		bool								RegisterProperty(TObject* pObj, 
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

			AddProperty(pProp);

			return true;
		}

	private:
		std::vector<PropertySetPtr>			m_PropSets;

		PropertySetPtr						m_pCurrentOwner;
	};
}
