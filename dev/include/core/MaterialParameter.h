#pragma once

#include "ShaderProgram.h"

namespace ld3d
{
	class _DLL_CLASS MaterialParameter
	{
	public:
		typedef std::pair<ShaderProgramPtr, ShaderProgram::ParameterID>	ParamInfo;


		MaterialParameter(const std::string& name, const std::vector<ParamInfo>& params);
		virtual ~MaterialParameter(void);

		const std::string&							GetName();

		bool										SetParameterBlock(void* data, uint64 bytes);

		void										SetParameterMatrix(const math::Matrix44& value);
		void										SetParameterFloat(float value);
		void										SetParameterInt(int32 value);
		void										SetParameterUInt(uint32 value);
		void										SetParameterBool(bool value);
		

		void										SetParameterColor(const math::Color4& value);

		void										SetParameterVector(const math::Vector2& value);
		void										SetParameterVector(const math::Vector3& value);
		void										SetParameterVector(const math::Vector4& value);
		void										SetParameterTexture(TexturePtr pTex);

		void										SetParameterSampler(SamplerStatePtr pSampler);

	private:
		std::string									m_name;

		std::vector<ParamInfo>						m_params;
	};

}
