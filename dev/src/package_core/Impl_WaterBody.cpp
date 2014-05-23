#include "core_ext_pch.h"
#include "Impl_WaterBody.h"

namespace ld3d
{
	Impl_WaterBody::Impl_WaterBody(GameObjectManagerPtr pManager):WaterBody(pManager)
	{
		m_size = 128;
	}


	Impl_WaterBody::~Impl_WaterBody(void)
	{
	}
	void Impl_WaterBody::SetSize(uint32 size)
	{
		m_size = size;
	}
	const uint32& Impl_WaterBody::GetSize() const
	{
		return m_size;
	}
}
