#include "voxel_pch.h"
#include "..\..\include\ext_voxel\Voxel.h"

namespace ld3d
{
	Voxel::Voxel(void)
	{
	}


	Voxel::~Voxel(void)
	{
	}
	const math::Vector3& Voxel::GetPos() const
	{
		return m_pos;
	}
	const math::Color4& Voxel::GetColor() const
	{
		return m_clr;
	}

	void Voxel::SetPos(const math::Vector3& pos)
	{
		m_pos = pos;
	}
	void Voxel::SetColor(const math::Color4& clr)
	{
		m_clr = clr;
	}
}