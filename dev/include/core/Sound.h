#pragma once


namespace ld3d
{
	class Sound
	{
	public:

		virtual void										Release()					= 0;
	protected:

		Sound(void){}
		virtual ~Sound(void){}
	};


}
