#pragma once

#include "core/Package.h"

namespace ld3d
{
	namespace water
	{
		class WaterPackage: public Package
		{
		public:
			WaterPackage(GameObjectManagerPtr pManager);
			virtual ~WaterPackage(void);

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
