#include "core_pch.h"
#include "..\..\include\core\TimerManager.h"
#include "core\Sys_Time.h"
#include "core_utils.h"

namespace ld3d
{
	TimerManager::TimerManager(void)
	{
		m_head = NULL;

	}


	TimerManager::~TimerManager(void)
	{
	}
	bool TimerManager::Init(Sys_TimePtr pTime)
	{
		m_pTime = pTime;

		m_head = (TimerNode*)mem_alloc(sizeof(TimerNode));
		memset(m_head, 0, sizeof(TimerNode));


		return true;
	}
	void TimerManager::Release()
	{
		//CleanRemove();
		TimerNode* pNode = m_head->next;

		while(pNode)
		{
			TimerNode* n = pNode;

			pNode = pNode->next;

			mem_free(n);
		}

		m_head->next = NULL;

		mem_free(m_head);

		m_remove.clear();
		
	}
	void TimerManager::CleanRemove()
	{
		for(size_t i = 0; i <m_remove.size(); ++i)
		{
			UnLink(m_remove[i]);
			if(m_remove[i])
			{
				mem_free(m_remove[i]);
				m_remove[i] = NULL;
			}
		}
		m_remove.clear();
	}

	void TimerManager::Update()
	{
		
		CleanRemove();
		uint64 tick = m_pTime->Tick();

		TimerNode* pNode = m_head->next;


		std::vector<TimerNode*> l;

		while(pNode)
		{

			if((tick - pNode->start_tick) < pNode->interval)
			{
				break;
			}

			TimerNode* pTmp = pNode;

			pNode = pNode->next;


			pTmp->handler(pTmp, pTmp->interval);
			

			UnLink(pTmp);

			l.push_back(pTmp);

		}

		for(size_t i = 0; i <l.size(); ++i)
		{
			InsertNode(l[i]);
		}
		CleanRemove();
	}
	TimerManager::timer_handle TimerManager::RegisterTimer(uint64 interval, const std::function<void (timer_handle, uint64)>& handler)
	{
		uint64 tick = m_pTime->Tick();

		TimerNode* pNewNode = (TimerNode*)mem_alloc(sizeof(TimerNode));;
		pNewNode->interval = interval;
		pNewNode->start_tick = tick;
		pNewNode->handler = handler;
		pNewNode->next = NULL;
		pNewNode->prev = NULL;

		InsertNode(pNewNode);

		return pNewNode;
	}
	void TimerManager::RemoveTimer(timer_handle timer)
	{
		if(timer == NULL)
			return;

		TimerNode* pNode = (TimerNode*)timer;
		m_remove.push_back(pNode);

	}
	void TimerManager::InsertNode(TimerNode* pNewNode)
	{
		uint64 tick = m_pTime->Tick();

		pNewNode->start_tick = tick;

		uint64 tn = pNewNode->start_tick + pNewNode->interval;

		TimerNode* pNode = m_head;

		while(pNode)
		{
			TimerNode* pNext = pNode->next;

			if(pNext == NULL)
			{
				pNode->next = pNewNode;
				pNewNode->prev = pNode;
				pNewNode->next = NULL;
				break;
			}


			if((pNext->start_tick + pNext->interval) > tn)
			{
				pNode->next = pNewNode;
				pNewNode->prev = pNode;

				pNewNode->next = pNext;
				pNext->prev = pNewNode;
				break;
			}

			pNode = pNode->next;
		}
	}
	void TimerManager::UnLink(TimerNode* pNode)
	{
		if(pNode == NULL)
			return;

		if(pNode->prev)
		{
			pNode->prev->next = pNode->next;
		}

		if(pNode->next)
		{
			pNode->next->prev = pNode->prev;
		}

		pNode->next = pNode->prev = NULL;

	}
}
