#pragma once

namespace ld3d
{
	class Voxel
	{
	public:
		Voxel(void);
		virtual ~Voxel(void);
		
		void																SetPos(const math::Vector3& pos);
		void																SetColor(const math::Color4& clr);

		const math::Vector3&												GetPos() const;
		const math::Color4&													GetColor() const;
	private:
		math::Vector3														m_pos;
		int																	m_type;
		math::Color4														m_clr;
	};
}
