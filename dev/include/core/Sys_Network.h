#pragma once

namespace ld3d
{
	class Sys_Network
	{
	public:

		/*virtual bool												Init()							= 0;
		virtual void												Release()						= 0;

		virtual void												Update()						= 0;



		virtual void												Listen()						= 0;
		virtual void												Connect()						= 0;

		virtual void												Accept()						= 0;

		virtual void												Recv()							= 0;
		virtual void												Send()							= 0;
		virtual void												Close()							= 0;*/


		virtual bool												Initialize()					= 0;
		virtual void												Release()						= 0;
		virtual void												Update()						= 0;
	protected:
		Sys_Network(void){}
		virtual ~Sys_Network(void){}
	};
}
