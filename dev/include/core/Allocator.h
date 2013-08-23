#pragma once

#include <platform/platform.h>

namespace ld3d
{
	class _DLL_CLASS Allocator
	{
	public:

		virtual void*								Alloc(uint64 bytes)					= 0;
		virtual void								Free(void* mem)						= 0;

		virtual void								Update(){}

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
}