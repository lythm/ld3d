#pragma once



#include "core/Package.h"


namespace ld3d
{
	namespace atmosphere
	{
		class AtmospherePackage : public Package
		{
		public:
			AtmospherePackage(GameObjectManagerPtr pManager);
			virtual ~AtmospherePackage(void);

			const char*															GetPackageName();
			int																	GetClassCount();
			ComponentClass*														GetClassByIndex(int index);

			int																	GetTemplateCount();
			GameObjectTemplate*													GetTemplateByIndex(int index);

			void																Release();

		private:
			GameObjectManagerPtr												m_pManager;

			std::vector<ComponentClass>											m_classes;
			std::vector<GameObjectTemplate*>									m_tpls;
		};


	}
}