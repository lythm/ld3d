#include "utils_pch.h"
#include "utils/StdAllocator.h"

namespace ld3d
{
	StdAllocator::StdAllocator(void)
	{
	}


	StdAllocator::~StdAllocator(void)
	{
	}
	void* StdAllocator::Alloc(uint64 bytes)
	{
		return new uint8[bytes];
	}
	void StdAllocator::Free(void* mem)
	{
		delete mem;
	}
	
}
