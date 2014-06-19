#include "utils_pch.h"
#include "utils/PoolAllocator.h"
#include "utils/utils_helper.h"



#ifndef CONTAINING_RECORD	
#define CONTAINING_RECORD(address, type, field) ((type *)( \
    (char *)(address) - \
    (ptrdiff_t)(&((type *)0)->field)))
#endif




namespace ld3d
{

	PoolAllocator::PoolAllocator(void)
	{
		m_allocBytes			= 0;
	}


	PoolAllocator::~PoolAllocator(void)
	{
	}
	void* PoolAllocator::Alloc(uint64 bytes)
	{
		uint64 req_bytes = sizeof(_MemBlock) + bytes;

		int i_pool = -1;
		for(size_t i = 0; i < m_pools.size(); ++i)
		{
			if(m_pools[i]->get_requested_size() >= req_bytes)
			{
				i_pool = (int)i;
				break;
			}
		}
		
		_MemBlock* block = nullptr;
		if(i_pool == -1)
		{
			block = (_MemBlock*)new char[req_bytes];
		}
		else
		{
			block = (_MemBlock*)m_pools[i_pool]->malloc();
		}
		block->bytes = bytes;

		m_allocBytes += req_bytes;
		return block->data;
	}
	void PoolAllocator::Free(void* mem)
	{
		if(mem == nullptr)
		{
			return;
		}
		_MemBlock* pNode = CONTAINING_RECORD(mem, _MemBlock, data);
		
		uint64 req_bytes = sizeof(_MemBlock) + pNode->bytes;

		int i_pool = -1;
		for(size_t i = 0; i < m_pools.size(); ++i)
		{
			if(m_pools[i]->get_requested_size() >= req_bytes)
			{
				i_pool = (int)i;
				break;
			}
		}
		
		if(i_pool == -1)
		{
			delete pNode;
		}
		else
		{
			m_pools[i_pool]->free(pNode);
		}
		m_allocBytes -= req_bytes;
	}
	bool PoolAllocator::Initialize()
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
			Pool_T* p = new Pool_T(v_list[i], 1024);
			
			m_pools.push_back(p);
		}

		m_allocBytes = 0;
		return true;
	}
	void PoolAllocator::Release()
	{
		m_allocBytes = 0;
		for(auto p :m_pools)
		{
			delete p;
		}

		m_pools.clear();

	}
	void PoolAllocator::Update()
	{
		
	}
	uint64 PoolAllocator::GetAllocatedBytes()
	{
		return m_allocBytes;
	}
}