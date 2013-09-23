#include "core_pch.h"
#include "core/PoolAllocator.h"

namespace ld3d
{

	PoolAllocator::PoolAllocator(void)
	{
	}


	PoolAllocator::~PoolAllocator(void)
	{
	}
	void* PoolAllocator::Alloc(uint64 bytes)
	{
		return m_pMemPool->Alloc(bytes);
	}
	void PoolAllocator::Free(void* mem)
	{
		m_pMemPool->Free(mem);
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
}