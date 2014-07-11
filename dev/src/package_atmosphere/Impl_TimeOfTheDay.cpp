#include "package_atmosphere_pch.h"
#include "Impl_TimeOfTheDay.h"


namespace ld3d
{
	namespace atmosphere
	{
		namespace impl
		{

			Impl_TimeOfTheDay::Impl_TimeOfTheDay(GameObjectManagerPtr pManager) : TimeOfTheDay(pManager)
			{
				SetVersion(g_packageVersion);
			}


			Impl_TimeOfTheDay::~Impl_TimeOfTheDay(void)
			{
			}
			bool Impl_TimeOfTheDay::OnAttach()
			{
				GameObjectComponentPtr pSkyDome = m_pManager->CreateComponent("Atmosphere.SkyDome");

				m_pObject->AddComponent(pSkyDome);

				GameObjectComponentPtr pSkyLight = m_pManager->CreateComponent("Atmosphere.SkyLight");

				m_pObject->AddComponent(pSkyLight);

				return true;
			}
			void Impl_TimeOfTheDay::OnDetach()
			{
			}
		}
	}
}
