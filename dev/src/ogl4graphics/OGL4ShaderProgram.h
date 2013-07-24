#pragma once

#include "core/ShaderProgram.h"

namespace ld3d
{
	class OGL4ShaderProgram : public ShaderProgram
	{
		struct TextureLink
		{
			GLuint											index;
			TexturePtr										pTex;
			SamplerStatePtr									pSampler;
		};
		struct UniformBlock
		{
			OGL4BufferPtr									pBuffer;
			GLuint											index;
			std::string										name;
		};


	public:
		OGL4ShaderProgram(void);
		virtual ~OGL4ShaderProgram(void);


		bool												AttachShaderFromFile(SHADER_TYPE type, const char* szFile);
		void												AttachShader(ShaderPtr pShader);

		bool												Link();
		bool												Validate();
		void												Release();


		ParameterID											FindParameterByName(const char* szName);
		ParameterID											FindParameterBlockByName(const char* szName);

		bool												SetParameterBlock(ParameterID param, void* data, uint64 bytes);

		void												SetParameterMatrix(ParameterID param, const math::Matrix44& value);
		
		void												SetParameterFloat(ParameterID param, float value);
		void												SetParameterInt(ParameterID param, int32 value);
		void												SetParameterUInt(ParameterID param, uint32 value);
		void												SetParameterBool(ParameterID param, bool value);

		void												SetParameterVector(ParameterID param, const math::Vector2& value);
		void												SetParameterVector(ParameterID param, const math::Vector3& value);
		void												SetParameterVector(ParameterID param, const math::Vector4& value);
		void												SetParameterTexture(ParameterID param, TexturePtr pTex);
		void												SetParameterSampler(ParameterID param, SamplerStatePtr pSampler);

		bool												Create();
		void												Use();


	private:
		void												CollectUniformBlocks();
		void												BindUniformBlocks();
		void												BindTextures();
	private:
		GLuint												m_program;


		std::vector<ShaderPtr>								m_shaders;

		std::vector<UniformBlock>							m_uniformBlocks;

		std::vector<TextureLink>							m_texLinks;
	};

}
