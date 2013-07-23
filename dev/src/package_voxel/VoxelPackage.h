#pragma once


#include "core\Package.h"

namespace ld3d
{
	class VoxelPackage : public Package
	{
	public:
		VoxelPackage(GameObjectManagerPtr pManager);
		virtual ~VoxelPackage(void);

		

		const wchar_t*						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);

		int									GetTemplateCount();
		GameObjectTemplate*					GetTemplateByIndex(int index);

		void								Release();
		
	private:

		GameObjectManagerPtr				m_pManager;
		std::vector<ComponentClass>			m_classes;
		std::vector<GameObjectTemplate*>	m_tpls;
	};
}
