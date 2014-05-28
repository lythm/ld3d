#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class CameraData : public GameObjectComponent
	{
	public:
		CameraData(GameObjectManagerPtr pManager) : GameObjectComponent("Camera", pManager){}
		virtual ~CameraData(void){}

		virtual void						UpdateCamera()									= 0;
		virtual void						SetViewport(const math::RectI& vp)				= 0;

	};
}
