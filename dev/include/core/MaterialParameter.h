#pragma once

#include "ShaderProgram.h"

namespace ld3d
{
	class EXPORT_CLASS MaterialParameter
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
		
		void										SetParameterVector(const math::Vector2& value);
		void										SetParameterVector(const math::Vector3& value);
		void										SetParameterVector(const math::Vector4& value);
		void										SetParameterTexture(Texture2Ptr pTex);

		void										SetParameterSampler(SamplerStatePtr pSampler);

	private:
		std::string									m_name;

		std::vector<ParamInfo>						m_params;
	};

	template <typename T>
	class EXPORT_CLASS MaterialParameter_T: public MaterialParameter
	{
	public:
		MaterialParameter_T(const std::string& name, std::function<void (const T&)> setter) : MaterialParameter(name)
		{
			m_setter = setter;
		}
		virtual ~MaterialParameter_T()
		{
		}

		void Set(const T& val)
		{
			m_setter(val);
		}

	private:
		std::function<void (const T&)>						m_setter;
	};

	typedef MaterialParameter_T<bool>						MaterialParameterBool;
	typedef MaterialParameter_T<int>						MaterialParameterInt;
	typedef MaterialParameter_T<float>						MaterialParameterFloat;
	typedef MaterialParameter_T<math::Vector2>				MaterialParameterFloat2;
	typedef MaterialParameter_T<math::Vector3>				MaterialParameterFloat3;
	typedef MaterialParameter_T<math::Vector4>				MaterialParameterFloat4;
	typedef MaterialParameter_T<math::Matrix44>				MaterialParameterFloat4x4;
	typedef MaterialParameter_T<TexturePtr>					MaterialParameterTexture;
	typedef MaterialParameter_T<SamplerStatePtr>			MaterialParameterSampler;
	

	typedef std::shared_ptr<MaterialParameterBool>			MaterialParameterBoolPtr;
	typedef std::shared_ptr<MaterialParameterInt>			MaterialParameterIntPtr;
	typedef std::shared_ptr<MaterialParameterFloat>			MaterialParameterFloatPtr;
	typedef std::shared_ptr<MaterialParameterFloat2>		MaterialParameterFloat2Ptr;
	typedef std::shared_ptr<MaterialParameterFloat3>		MaterialParameterFloat3Ptr;
	typedef std::shared_ptr<MaterialParameterFloat4>		MaterialParameterFloat4Ptr;
	typedef std::shared_ptr<MaterialParameterFloat4x4>		MaterialParameterFloat4x4Ptr;
	typedef std::shared_ptr<MaterialParameterTexture>		MaterialParameterTexturePtr;
	typedef std::shared_ptr<MaterialParameterSampler>		MaterialParameterSamplerPtr;

}
