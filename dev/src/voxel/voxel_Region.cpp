#include "voxel_pch.h"
#include "..\..\include\voxel\voxel_Region.h"

namespace ld3d
{
	namespace voxel
	{
		Region::Region(void)
		{
			Reset();
		}


		Region::~Region(void)
		{
		}
		bool Region::Load()
		{
			return true;
		}
		bool Region::Save()
		{
			return true;
		}
		bool Region::Gen(WorldGenPtr pGen)
		{
			return true;
		}
		bool Region::IsModified() const
		{
			return m_modified;
		}
		void Region::SetModified()
		{
			m_modified = true;
		}
		void Region::Reset()
		{
			m_modified = false;
			m_chunks.clear();
			m_chunks.resize(REGION_SIZE * REGION_SIZE);
		}
	}
}
