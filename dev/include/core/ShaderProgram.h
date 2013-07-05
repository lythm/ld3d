#pragma once

namespace ld3d
{
	class ShaderProgram
	{
	public:


		virtual void												Release()										= 0;

	protected:
		ShaderProgram(void){}

		virtual ~ShaderProgram(void){}
	};


}
