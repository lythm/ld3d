#pragma once

namespace ld3d
{
	template<typename T>
	class RefCount
	{
	public:

		RefCount(void) : m_ref(1){}
		virtual ~RefCount(void){}

		void		IncRef()
		{
			++m_ref;
		}
		void		DecRef()
		{
			--m_ref;
		}
		T			GetRef() const
		{
			return m_ref;
		}


	private:
		RefCount(const RefCount& other);
		const RefCount& operator=(const RefCount& other);
	private:

		T			m_ref;
	};
}