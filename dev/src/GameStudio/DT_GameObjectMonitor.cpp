#include "stdafx.h"
#include "DT_GameObjectMonitor.h"

namespace dt
{
	ld3d::ExtPackage::ComponentClass							DT_GameObjectMonitor::s_class(L"DT_GameObjectMonitor",
																						L"DT",
																						L"Game Object Monitor",
																						&DT_GameObjectMonitor::Create);

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
	ld3d::GameObjectComponentPtr DT_GameObjectMonitor::Create(ld3d::GameObjectManagerPtr pManager)
	{
		using namespace ld3d;

		return GameObjectComponentPtr(new DT_GameObjectMonitor(pManager));
	}
	
}
