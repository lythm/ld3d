#include "package_water_pch.h"

#include "WaterPackage.h"


_DLL_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	return new ld3d::water::WaterPackage(pManager);
}


_DLL_API void DestroyPackage(ld3d::Package* pPackage)
{
	delete (ld3d::water::WaterPackage*)pPackage;
}


namespace ld3d
{
	namespace water
	{
		WaterPackage::WaterPackage(GameObjectManagerPtr pManager)
		{
			m_pManager			= pManager;
		}


		WaterPackage::~WaterPackage(void)
		{
		}
		void WaterPackage::Release()
		{
			m_classes.clear();
			for(size_t i = 0; i < m_tpls.size(); ++i)
			{
				m_tpls[i]->Release();
				delete m_tpls[i];
			}
			m_tpls.clear();
		}
		const char* WaterPackage::GetPackageName()
		{
			return "Water";
		}

		int WaterPackage::GetClassCount()
		{
			return (int)m_classes.size();
		}
		WaterPackage::ComponentClass* WaterPackage::GetClassByIndex(int index)
		{
			return &m_classes[index];
		}
		int	WaterPackage::GetTemplateCount()
		{
			return (int)m_tpls.size();
		}
		GameObjectTemplate* WaterPackage::GetTemplateByIndex(int index)
		{
			return m_tpls[index];
		}
	}

}