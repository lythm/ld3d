#include "stdafx.h"
#include "DT_GameObjectMonitor.h"
#include "editor_utils.h"

namespace dt
{
	ld3d::ExtPackage::ComponentClass							DT_GameObjectMonitor::s_class(L"DT_GameObjectMonitor",
																						L"DT",
																						L"Game Object Monitor",
																						&ld3d::Create_Component<DT_GameObjectMonitor>);

	DT_GameObjectMonitor::DT_GameObjectMonitor(ld3d::GameObjectManagerPtr pManager) : GameObjectComponent(L"DT_GameObjectMonitor", pManager)
	{
		SetVersion(ld3d::Version(0, 0, 0, 1));
	}


	DT_GameObjectMonitor::~DT_GameObjectMonitor(void)
	{
	}
	void DT_GameObjectMonitor::AddMonitor(const Monitor& m)
	{
		m_monitors.connect(m);
	}
	void DT_GameObjectMonitor::Alert()
	{
		m_monitors(GetGameObject());
	}
	ld3d::ExtPackage::ComponentClass* DT_GameObjectMonitor::GetClass()
	{
		return &s_class;
	}
}
