#include "gameeditor_ext_pch.h"
#include "..\..\include\ext_dt\DT_Observor.h"

namespace ld3d
{
	DT_Observor::DT_Observor(GameObjectManagerPtr pManager): GameObjectComponent(L"DT_Gizmo", pManager)
	{
	}


	DT_Observor::~DT_Observor(void)
	{
	}

}