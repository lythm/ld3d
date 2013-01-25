#pragma once

namespace ld3d
{

	class EXPORT_CLASS DT_Observor: public GameObjectComponent
	{
	public:
		DT_Observor(GameObjectManagerPtr pManager);
		virtual ~DT_Observor(void);
	};


}