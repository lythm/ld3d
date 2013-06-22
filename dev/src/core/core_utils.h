#pragma once

#include "core\CoreApi.h"
#include "core\Allocator.h"

namespace ld3d
{
	inline
		void*												mem_alloc(uint64 bytes)
	{
		return CoreApi::GetAllocator()->Alloc(bytes);
	}
	inline
		void												mem_free(void* pMem)
	{
		CoreApi::GetAllocator()->Free(pMem);
	}

	template<typename T> inline
		std::shared_ptr<T>									alloc_object()
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator());
	}

	template<typename T, typename TP> inline
		std::shared_ptr<T>									alloc_object(TP& p)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(CoreApi::GetAllocator(), p);
	}

	inline
		void												log(const std::wstring& text)
	{
		CoreApi::Log(text);
	}

}