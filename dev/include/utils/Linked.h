#pragma once

namespace ld3d
{
	template <typename T>
	class Linked : public std::enable_shared_from_this<Linked<T>>
	{
	public:
		typedef std::shared_ptr<T>					LinkedNodePtr;

		Linked(){}
		virtual ~Linked(){}

		LinkedNodePtr								Next()
		{
			return m_next;
		}
		LinkedNodePtr								Prev()
		{
			return m_prev;
		}

		// insert after me
		void										Insert(LinkedNodePtr pNode)
		{
			Insert(std::dynamic_pointer_cast<T>(shared_from_this()), pNode);
		}
		// insert after pPos
		static void									Insert(LinkedNodePtr pPos, LinkedNodePtr pNode)
		{
			if(pNode == nullptr || pPos == nullptr)
				return;

			pNode->Unlink();

			if(pPos->m_next != nullptr)
			{
				pPos->m_next->m_prev = pNode;
			}

			pNode->m_next = pPos->m_next;

			pPos->m_next = pNode;
			pNode->m_prev = pPos;
		}

		void										Unlink()
		{
			if(m_next != nullptr)
			{
				m_next->m_prev = m_prev;
			}
			if(m_prev != nullptr)
			{
				m_prev->m_next = m_next;
			}

			m_next.reset();
			m_prev.reset();

		}
		
	private:

		LinkedNodePtr										m_prev;
		LinkedNodePtr										m_next;

	};
}
