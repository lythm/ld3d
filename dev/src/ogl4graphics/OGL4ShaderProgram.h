#pragma once

#include "core/ShaderProgram.h"

namespace ld3d
{
	class OGL4ShaderProgram : public ShaderProgram
	{
	public:
		OGL4ShaderProgram(void);
		virtual ~OGL4ShaderProgram(void);


		bool												AttachShaderFromFile(SHADER_TYPE type, const char* szFile);
		void												AttachShader(ShaderPtr pShader);

		bool												Link();
		bool												Validate();
		void												Release();






		bool												Create();
		void												Use();

	private:
		GLuint												m_program;


		std::vector<ShaderPtr>								m_shaders;
	};


}
