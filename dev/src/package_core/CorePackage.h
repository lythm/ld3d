#pragma once

#include "core/Package.h"

namespace ld3d
{
	class CorePackage : public Package
	{
	public:
		CorePackage(GameObjectManagerPtr pManager);
		virtual ~CorePackage(void);

		const wchar_t*						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);


		int									GetTemplateCount();
		GameObjectTemplate*					GetTemplateByIndex(int index);


		void								Release();
	private:
		void								RegisterClasses();
		void								RegisterTemplates();

	private:
		GameObjectManagerPtr				m_pManager;

		std::vector<ComponentClass>			m_classes;

		std::vector<GameObjectTemplate*>	m_tpls;
	};
}
