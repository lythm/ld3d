#include "package_atmosphere_pch.h"
#include "AtmospherePackage.h"
#include "Impl_SkyDome.h"



_DLL_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	return new ld3d::atmosphere::AtmospherePackage(pManager);
}


_DLL_API void DestroyPackage(ld3d::Package* pPackage)
{
	delete (ld3d::atmosphere::AtmospherePackage*)pPackage;
}


namespace ld3d
{
	namespace atmosphere
	{
		AtmospherePackage::AtmospherePackage(GameObjectManagerPtr pManager)
		{
			m_pManager			= pManager;


			m_classes.push_back(ComponentClass("Atmosphere.SkyDome",
				"Atmosphere",
				"Sky Dome",
				&Create_Component<Impl_SkyDome>));

		}


		AtmospherePackage::~AtmospherePackage(void)
		{
		}
		void AtmospherePackage::Release()
		{
			m_classes.clear();
			for(size_t i = 0; i < m_tpls.size(); ++i)
			{
				m_tpls[i]->Release();
				delete m_tpls[i];
			}
			m_tpls.clear();
		}
		const char* AtmospherePackage::GetPackageName()
		{
			return "Atmosphere";
		}

		int AtmospherePackage::GetClassCount()
		{
			return (int)m_classes.size();
		}
		AtmospherePackage::ComponentClass* AtmospherePackage::GetClassByIndex(int index)
		{
			return &m_classes[index];
		}
		int	AtmospherePackage::GetTemplateCount()
		{
			return (int)m_tpls.size();
		}
		GameObjectTemplate* AtmospherePackage::GetTemplateByIndex(int index)
		{
			return m_tpls[index];
		}
	}

}