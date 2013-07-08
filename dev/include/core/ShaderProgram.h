#pragma once

namespace ld3d
{
	class ShaderProgram
	{
	public:


		virtual void												Release()														= 0;
		virtual bool												AttachShaderFromFile(SHADER_TYPE type, const char* szFile)		= 0;
		virtual void												AttachShader(ShaderPtr pShader)									= 0;

		virtual bool												Link()															= 0;
		virtual bool												Validate()														= 0;
	protected:
		ShaderProgram(void){}

		virtual ~ShaderProgram(void){}
	};


}
