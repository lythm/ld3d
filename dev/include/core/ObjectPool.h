#pragma once

namespace ld3d
{
	//!  ObjectPool
	/*!
	This class is designed to present an object cache, with which we can resuse some object without
	new or delete it from the heap directly. It's more efficient this way.

	@date 05/13/2003
	@version 1.0
	@author Dan Tong
	@author mail: Lythm780522@gmail.com
	*/

	template <class T>
	class ObjectPool  
	{
	public:
		//!  Constructor
		ObjectPool():m_free(0),m_pool(0), m_nCount(0), m_nObjAllocated(0){}

		//!  Destructor
		virtual ~ObjectPool(){	DestroyPool(); }

		//!  CreatePool
		/*!
		Create the pool with specified pool capacity, in object count.
		@param nObj Max number of object the pool contain.
		@return None
		*/
		bool CreatePool(int nObj)
		{
			m_nObjAllocated = 0;
			m_nCount = nObj;
			m_pool = (ItemNode*) new char[sizeof(ItemNode) * nObj];
			if(m_pool == 0)
				return false;
			for(int i =0; i < nObj - 1; ++i)
			{
				(m_pool+i)->next = m_pool+i+1;
			}
			m_pool[nObj - 1].next = 0;
			m_free = m_pool;
			return true;
		}
		//!  DestroyPool
		/*!
		Destroy the pool, release resources.
		*/
		void DestroyPool()
		{
			delete [](char*)m_pool;
			m_nObjAllocated = 0;
			m_pool = NULL;	
		}

		//!  AllocRaw
		/*!
		Alloc memory from the pool, 
		@warning The constructor of the object wont be called.
		@return The object pointer.
		*/
		T* AllocRaw()
		{
			T* pObj = (T*)m_free;
			if(pObj != NULL)
			{
				m_free = m_free->next;
				++m_nObjAllocated;
			}
			return pObj;
		}
		//!  Alloc
		/*!
		Alloc an object from the pool, constructor of the object will be invoked.
		@return The object pointer.
		*/
		T* Alloc(){	return new(AllocRaw()) T;}

		//!  Return
		/*!
		Return the memory back to the pool.
		@warn:  The destructor of the object wont be invoked.

		@param pObj Object to return.
		*/
		void FreeRaw(void* pObj)
		{
			--m_nObjAllocated;
			((ItemNode*)pObj)->next = m_free;
			m_free = (ItemNode*)pObj;
		}
		//!  Return
		/*!
		Return the object to the pool.
		@param pObj Object to return.
		*/
		void Free(T* pObj)
		{
			pObj->~T();
			FreeRaw(pObj);
		}

		//!  PoolSize
		/*!
		The Pool size in bytes
		@return The pool size in bytes
		*/
		int PoolSize(){	return m_nCount * sizeof(T);}
		//!  ObjCount
		/*!
		The max number of object the pool can hold.
		@return The max number of object the pool can hold.
		*/
		int ObjCount() { return m_nCount;}

		//!  PoolUsed
		/*!
		The currently used bytes
		@return The currently used bytes
		*/
		int PoolUsed(){ return m_nObjAllocated * sizeof(T); }

		//!  ObjUsed
		/*!
		The object count current allocated from the pool.
		@return The object count current allocated from the pool.
		*/
		int ObjUsed(){ return m_nObjAllocated; }

	private:

		union ItemNode
		{
			struct {T		data;};
			ItemNode*	next;
		};

	private:
		int			m_nCount;
		int			m_nObjAllocated;
		ItemNode*	m_free;
		ItemNode*	m_pool;
	};
}