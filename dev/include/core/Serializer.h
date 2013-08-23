#pragma once




namespace ld3d
{
	class _DLL_CLASS Serializer
	{
	protected:
		Serializer(DataStreamPtr pStream)
		{
			m_pStream = pStream;
		}
		virtual ~Serializer(void)
		{
			m_pStream.reset();
		}




	protected:
		DataStreamPtr										m_pStream;
	};
}
