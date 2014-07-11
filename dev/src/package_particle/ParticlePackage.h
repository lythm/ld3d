#pragma once


#include "core/Package.h"

namespace ld3d
{
	namespace particle
	{
		class ParticlePackage: public Package
		{
		public:
			ParticlePackage(GameObjectManagerPtr pManager);
			virtual ~ParticlePackage(void);

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