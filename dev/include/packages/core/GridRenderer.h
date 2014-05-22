#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class GridRenderer : public GameObjectComponent
	{
	public:
		GridRenderer(GameObjectManagerPtr pManager) : GameObjectComponent("GridRenderer", pManager){}
		virtual ~GridRenderer(void){}

		virtual void													SetSize(uint32 size)											= 0;
		virtual void													SetGridSize(uint32 gridSize)									= 0;

		virtual uint32													GetSize()														= 0;
		virtual uint32													GetGridSize()													= 0;
		
		virtual void													SetColor(const math::Color4& clr)								= 0;
		virtual const math::Color4&										GetColor() const												= 0;
	};


}
