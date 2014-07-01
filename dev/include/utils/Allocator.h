#pragma once

#include "platform/platform.h"

namespace ld3d
{
	class _DLL_CLASS Allocator
	{
	public:

		virtual void*								Alloc(uint64 bytes)					= 0;
		virtual void								Free(void* mem)						= 0;

		virtual void								Update(){}

		virtual uint64								GetAllocatedBytes()					= 0;
	protected:

		Allocator(void){}
		virtual ~Allocator(void){}
	};


	template<typename T>
	class std_allocator_adapter
	{
	public:
		// type definitions
		typedef T							value_type;
		typedef T*							 pointer;
		typedef const T*					const_pointer;
		typedef T&							reference;
		typedef const T&					const_reference;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;

		template <class U>
		struct rebind 
		{
			typedef std_allocator_adapter<U> other;
		};

		pointer address (reference value) const 
		{
			return &value;
		}
		const_pointer address (const_reference value) const
		{
			return &value;
		}

		std_allocator_adapter(Allocator* a) throw() 
		{
			m_pAllocator = a;
		}
		std_allocator_adapter(const std_allocator_adapter& other) throw() 
		{
			m_pAllocator = other.m_pAllocator;
		}
		template <class U>
		std_allocator_adapter (const std_allocator_adapter<U>& other) throw() 
		{
			m_pAllocator = other.get_allocator();
		}
		~std_allocator_adapter() throw() 
		{
			m_pAllocator = nullptr;
		}

		size_type max_size () const throw() 
		{
			return 0xffffffff / sizeof(T);
		}

		pointer allocate (size_type num, const void* = 0) 
		{
			return (pointer)m_pAllocator->Alloc(num * sizeof(T));
		}

		void construct (pointer p, const T& value) 
		{
			new((void*)p)T(value);
		}

		void destroy (pointer p) 
		{
			p->~T();
		}

		void deallocate (pointer p, size_type num) 
		{
			m_pAllocator->Free((void*)p);
		}

		Allocator* get_allocator() const
		{
			return m_pAllocator;
		}
	private:
		Allocator*				m_pAllocator;
	};




	inline
		void*												mem_alloc(Allocator* a, uint64 bytes)
	{
		return a->Alloc(bytes);
	}
	inline
		void												mem_free(Allocator* a, void* pMem)
	{
		a->Free(pMem);
	}

	template<typename T> inline
		std::shared_ptr<T>									alloc_object(Allocator* a)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(a);
	}

	template<typename T, typename TP> inline
		std::shared_ptr<T>									alloc_object(Allocator* a, const TP& p)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(a, p);
	}



	template<typename T, typename TP1, typename TP2> inline
		std::shared_ptr<T>									alloc_object(Allocator* a, const TP1& p1, const TP2& p2)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(a, p1, p2);
	}

	template<typename T, typename TP1, typename TP2, typename TP3> inline
		std::shared_ptr<T>									alloc_object(Allocator* a, const TP1& p1, const TP2& p2, const TP3& p3)
	{
		return std::allocate_shared<T, std_allocator_adapter<T> >(a, p1, p2, p3);
	}

	//////////////
	template<typename T> inline
		T*													alloc_object_rawptr(Allocator* a)
	{
		void* mem = a->Alloc(sizeof(T));
		return new(mem)T();
	}

	template<typename T, typename TP> inline
		T*													alloc_object_rawptr(Allocator* a, const TP& p)
	{
		void* mem = a->Alloc(sizeof(T));
		return new(mem)T(p);
	}



	template<typename T, typename TP1, typename TP2> inline
		T*													alloc_object_rawptr(Allocator* a, const TP1& p1, const TP2& p2)
	{
		void* mem = a->Alloc(sizeof(T));
		return new(mem)T(p1, p2);
	}

	template<typename T, typename TP1, typename TP2, typename TP3> inline
		T*													alloc_object_rawptr(Allocator* a, const TP1& p1, const TP2& p2, const TP3& p3)
	{
		void* mem = a->Alloc(sizeof(T));
		return new(mem)T(p1, p2, p3);
	}

	template<typename T> inline
		void												free_object(Allocator* a, T* pObj)
	{
		if(pObj == nullptr)
		{
			return;
		}
		pObj->~T();
		a->Free(pObj);
	}
}
