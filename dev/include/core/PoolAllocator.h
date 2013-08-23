#pragma once

#include "core/Allocator.h"

namespace ld3d
{
	class _DLL_CLASS PoolAllocator : public Allocator
	{
		typedef std::shared_ptr<MemPool>				MemPoolPtr;
	public:
		PoolAllocator(void);
		virtual ~PoolAllocator(void);

		void*											Alloc(uint64 bytes);
		void											Free(void* mem);

		bool											Initialize();
		void											Release();

		void											Update();
	private:
		MemPoolPtr										m_pMemPool;
	};


}