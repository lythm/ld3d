#pragma once


namespace ld3d
{
	class MaterialParameter
	{
	public:

		MaterialParameter(const std::string& name);
		virtual ~MaterialParameter(void);

		const std::string&							GetName();

	private:
		std::string									m_name;
	};

	template <typename T>
	class MaterialParameter_T: public MaterialParameter
	{
	public:
		MaterialParameter_T(const std::string& name, void* val) : MaterialParameter(name)
		{
			m_val = val;
		}
		virtual ~MaterialParameter_T()
		{
		}

		void Set(const T& val)
		{
			*((T*)m_val) = val;
		}

	private:
		void*												m_val;
	};

	typedef MaterialParameter_T<bool>						MaterialParameterBool;
	typedef MaterialParameter_T<int>						MaterialParameterInt;
	typedef MaterialParameter_T<float>						MaterialParameterFloat;
	typedef MaterialParameter_T<math::Vector2>				MaterialParameterFloat2;
	typedef MaterialParameter_T<math::Vector3>				MaterialParameterFloat3;
	typedef MaterialParameter_T<math::Vector4>				MaterialParameterFloat4;
	typedef MaterialParameter_T<math::Matrix44>				MaterialParameterFloat4x4;
	typedef MaterialParameter_T<TexturePtr>					MaterialParameterTexture;
	

	typedef std::shared_ptr<MaterialParameterBool>		MaterialParameterBoolPtr;
	typedef std::shared_ptr<MaterialParameterInt>			MaterialParameterIntPtr;
	typedef std::shared_ptr<MaterialParameterFloat>		MaterialParameterFloatPtr;
	typedef std::shared_ptr<MaterialParameterFloat2>		MaterialParameterFloat2Ptr;
	typedef std::shared_ptr<MaterialParameterFloat3>		MaterialParameterFloat3Ptr;
	typedef std::shared_ptr<MaterialParameterFloat4>		MaterialParameterFloat4Ptr;
	typedef std::shared_ptr<MaterialParameterFloat4x4>	MaterialParameterFloat4x4Ptr;
	typedef std::shared_ptr<MaterialParameterTexture>		MaterialParameterTexturePtr;

}
