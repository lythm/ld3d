#pragma once

#include "packages/core/CameraData.h"

namespace ld3d
{
	class Impl_CameraData : public CameraData
	{
	public:
		Impl_CameraData(GameObjectManagerPtr pManager);
		virtual ~Impl_CameraData(void);

		void						SetViewport(const math::RectI& vp);
		bool						OnAttach();
		void						OnDetach();
		bool						OnSerialize(DataStream* pStream);
		bool						OnUnSerialize(DataStream* pStream, const Version& version);

		void						Update(float dt);
		void						UpdateCamera();
		CameraPtr					GetCamera();

		void						SetNearPlane(float np);
		void						SetFarPlane(float fp);
		void						SetAspect(float aspect);
		void						SetFOV(float fov);
	private:
		CameraPtr					m_pCamera;

		float						m_np;
		float						m_fp;
		float						m_aspect;
		float						m_fov;
	};
}