#pragma once

#include "core/core_all.h"

#include "core/GameInterface.h"

namespace ld3d
{
	class UIViewer : public GameInterface
	{
	public:
		UIViewer(void);
		virtual ~UIViewer(void);

		bool									Initialize(ld3d::CoreApiPtr pCore);
		void									Release();
		bool									Update(float dt);

	private:
		CoreApiPtr								m_pCore;

		HtmlOverlayPtr							m_pPage;
	};


}