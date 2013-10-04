#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class CameraData : public GameObjectComponent
	{
	public:
		CameraData(GameObjectManagerPtr pManager);
		virtual ~CameraData(void);

		bool						OnAttach();
		void						OnDetach();
		bool						OnSerialize(DataStream* pStream);
		bool						OnUnSerialize(DataStream* pStream, const Version& version);

		void						Update(float dt);

		CameraPtr					GetCamera();
	private:
		CameraPtr					m_pCamera;
	};
}
