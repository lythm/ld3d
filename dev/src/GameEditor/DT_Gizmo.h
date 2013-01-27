#pragma once

namespace dt
{
	class DT_Gizmo : public ld3d::GameObjectComponent
	{
	public:
		DT_Gizmo(ld3d::GameObjectManagerPtr pManager);
		virtual ~DT_Gizmo(void);
	};


}