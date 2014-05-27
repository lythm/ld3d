#pragma once

#include "core/Allocator.h"

namespace ld3d
{
	class _DLL_CLASS StdAllocator : public Allocator
	{
	public:
		StdAllocator(void);
		virtual ~StdAllocator(void);

		void*								Alloc(uint64 bytes);
		void								Free(void* mem);

		uint64								GetTotalBytes();
		uint64								GetBytesLeft();

	private:
		
	};
}