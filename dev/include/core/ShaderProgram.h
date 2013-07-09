#pragma once

namespace ld3d
{
	class ShaderProgram
	{
	public:
		typedef int64												ParameterID;

		virtual void												Release()																= 0;
		virtual bool												AttachShaderFromFile(SHADER_TYPE type, const char* szFile)				= 0;
		virtual void												AttachShader(ShaderPtr pShader)											= 0;

		virtual bool												Link()																	= 0;
		virtual bool												Validate()																= 0;

		virtual ParameterID											FindParameterByName(const char* szName)									= 0;

		virtual ParameterID											FindParameterBlockByName(const char* szName)							= 0;


		
		virtual bool												SetParameterBlock(ParameterID param, void* data, uint64 bytes)			= 0;

		virtual void												SetParameterMatrix(ParameterID param, const math::Matrix44& value)		= 0;
		virtual void												SetParameterFloat(ParameterID param, float value)						= 0;
		virtual void												SetParameterInt(ParameterID param, int32 value)							= 0;
		virtual void												SetParameterUInt(ParameterID param, uint32 value)						= 0;
		virtual void												SetParameterBool(ParameterID param, bool value)							= 0;
		
		virtual void												SetParameterVector(ParameterID param, const math::Vector2& value)		= 0;
		virtual void												SetParameterVector(ParameterID param, const math::Vector3& value)		= 0;
		virtual void												SetParameterVector(ParameterID param, const math::Vector4& value)		= 0;

		
	protected:
		ShaderProgram(void){}

		virtual ~ShaderProgram(void){}
	};
}

