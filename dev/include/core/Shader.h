#pragma once

namespace ld3d
{
	class Shader
	{
	public:

		virtual void								Release()												= 0;
	protected:

		Shader(void){}

		virtual ~Shader(void){}
	};


}
