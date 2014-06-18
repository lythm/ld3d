#include "core_pch.h"
#include "core/PoolAllocator.h"

namespace ld3d
{

	PoolAllocator::PoolAllocator(void)
	{
		uint64 v_list[] =
		{
			8,
			2 * 8,
			3 * 8,
			4 * 8,
			5 * 8,
			6 * 8,
			7 * 8,
			8 * 8,
			16 * 8,
			32 * 8,
			64 * 8,
			128 * 8,
			256 * 8,
			512 * 8,
			1024 * 8,
			2048 * 8,
			4096 * 8,
			8192 * 8,
			
		};
		
		for(size_t i = 0; i < sizeof(v_list) / sizeof(v_list[0]); ++i)
		{
			boost::pool<pool_allocator> p(v_list[i]);
			
			m_pools.push_back(p);
		}
	}


	PoolAllocator::~PoolAllocator(void)
	{
	}
	void* PoolAllocator::Alloc(uint64 bytes)
	{
		int i_pool = -1;
		for(size_t i = 0; i < m_pools.size(); ++i)
		{
			if(m_pools[i].get_requested_size() >= bytes)
			{
				i_pool = (int)i;
				break;
			}
		}
		
		if(i_pool == -1)
		{
			return new char[bytes];
		}
		
		return m_pools[i_pool].malloc();

		//return m_pMemPool->Alloc(bytes);
	}
	void PoolAllocator::Free(void* mem)
	{
		for(auto& pool : m_pools)
		{
			if(pool.is_from(mem))
			{
				pool.free(mem);
				return;
			}
		}
		//m_pMemPool->Free(mem);
	}
	bool PoolAllocator::Initialize()
	{
		m_pMemPool = MemPoolPtr(new MemPool);
		if(m_pMemPool->Initialize() == false)
		{
			return false;
		}
		return true;
	}
	void PoolAllocator::Release()
	{
		_release_and_reset(m_pMemPool);

	}
	void PoolAllocator::Update()
	{
		if(m_pMemPool)
		{
			m_pMemPool->Update();
		}
	}
	uint64 PoolAllocator::GetTotalBytes()
	{
		return m_pMemPool ? m_pMemPool->GetTotalBytes() : 0;
	}
	uint64 PoolAllocator::GetBytesLeft()
	{
		return m_pMemPool ? m_pMemPool->GetBytesLeft() : 0;
	}
}