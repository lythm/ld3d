#pragma once

#include "packages/core/CameraData.h"

namespace ld3d
{
	class Impl_CameraData : public CameraData
	{
	public:
		Impl_CameraData(GameObjectManagerPtr pManager);
		virtual ~Impl_CameraData(void);

		bool						OnAttach();
		void						OnDetach();
		bool						OnSerialize(DataStream* pStream);
		bool						OnUnSerialize(DataStream* pStream, const Version& version);

		void						Update(float dt);
		void						UpdateCamera();
		CameraPtr					GetCamera();
	private:
		CameraPtr					m_pCamera;
	};
}