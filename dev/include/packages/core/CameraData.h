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

		virtual void						SetNearPlane(float np)							= 0;
		virtual void						SetFarPlane(float fp)							= 0;
		virtual void						SetAspect(float aspect)							= 0;
		virtual void						SetFOV(float fov)								= 0;

	};
}
