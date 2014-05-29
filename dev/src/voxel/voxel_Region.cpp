#include "voxel_pch.h"
#include "voxel/voxel_Region.h"
#include "voxel/voxel_World.h"
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
		void Region::Reset(const Coord& coord)
		{
			m_modified		= false;
			m_coord			= coord;
			m_loaded		= false;
			m_refCount		= 0;
		}
		bool Region::Initialize(WorldPtr pWorld, const Coord& coord)
		{
			m_pWorld = pWorld;
			m_pChunkManager = pWorld->GetChunkManager();

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
		void Region::IncRef()
		{
			++m_refCount;
		}
		void Region::DecRef()
		{
			--m_refCount;
		}
		int32 Region::GetRef() const
		{
			return m_refCount;
		}
		bool Region::Unload()
		{
			return Save();
		}
	}
}

