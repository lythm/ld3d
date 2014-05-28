#include "voxel_pch.h"
#include "..\..\include\voxel\voxel_Region.h"

namespace ld3d
{
	namespace voxel
	{
		Region::Region(void)
		{
			Reset(Coord());
		}


		Region::~Region(void)
		{
		}
		bool Region::Load(WorldGenPtr pGen)
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
		void Region::Reset(const Coord& coord)
		{
			m_modified = false;
			m_coord = coord;
			m_loaded = false;
		}
		bool Region::Initialize(ChunkManagerPtr pChunkManager, const Coord& coord)
		{
			m_pChunkManager = pChunkManager;

			Reset(coord);

			return true;
		}
		void Region::Release()
		{
			m_modified = false;
			m_coord = Coord();

			m_pChunkManager.reset();
		}
		const Coord& Region::GetRegionCoord() const
		{
			return m_coord;
		}
		void Region::SetRegionCoord(const Coord& coord)
		{
			m_coord = coord;
		}
		bool Region::IsLoaded() const
		{
			return m_loaded;
		}
		void Region::SetLoaded(bool loaded)
		{
			m_loaded = loaded;
		}
	}
}

