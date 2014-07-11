#include "particle_pch.h"
#include "ParticlePackage.h"



_DLL_API ld3d::Package* CreatePackage(ld3d::GameObjectManagerPtr pManager)
{
	return new ld3d::particle::ParticlePackage(pManager);
}


_DLL_API void DestroyPackage(ld3d::Package* pPackage)
{
	delete (ld3d::particle::ParticlePackage*)pPackage;
}

namespace ld3d
{
	namespace particle
	{
		
		ParticlePackage::ParticlePackage(GameObjectManagerPtr pManager)
		{
			m_pManager			= pManager;


			/*m_classes.push_back(ComponentClass("Atmosphere.SkyDome",
				"Atmosphere",
				"Sky Dome",
				&Create_Component<Impl_SkyDome>));*/

		}


		ParticlePackage::~ParticlePackage(void)
		{
		}
		void ParticlePackage::Release()
		{
			m_classes.clear();
			for(size_t i = 0; i < m_tpls.size(); ++i)
			{
				m_tpls[i]->Release();
				delete m_tpls[i];
			}
			m_tpls.clear();
		}
		const char* ParticlePackage::GetPackageName()
		{
			return "Particle";
		}

		int ParticlePackage::GetClassCount()
		{
			return (int)m_classes.size();
		}
		ParticlePackage::ComponentClass* ParticlePackage::GetClassByIndex(int index)
		{
			return &m_classes[index];
		}
		int	ParticlePackage::GetTemplateCount()
		{
			return (int)m_tpls.size();
		}
		GameObjectTemplate* ParticlePackage::GetTemplateByIndex(int index)
		{
			return m_tpls[index];
		}
	}
}
