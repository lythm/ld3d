#pragma once

namespace ld3d
{
	class VoxelBlock
	{
	public:
		VoxelBlock(void);
		virtual ~VoxelBlock(void);


		const math::Vector3&							Center();

	private:
		math::Vector3									m_center;

		VoxelPtr										m_voxels[4][4];
	};
}
