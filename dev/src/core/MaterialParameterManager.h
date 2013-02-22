#pragma once

namespace ld3d
{
	class MaterialParameterManager
	{
	public:
		MaterialParameterManager(void);
		virtual ~MaterialParameterManager(void);

		bool																AddParameter(MaterialParameterPtr pParam);
		bool																Exist(const std::string& name);

		uint32																GetParameterCount();
		MaterialParameterPtr												GetParameterByIndex(uint32 index);
		MaterialParameterPtr												GetParameterByName(const std::string& name);

	private:

		boost::unordered_map<std::string, MaterialParameterPtr>				m_parameterMap;
		std::vector<MaterialParameterPtr>									m_params;
	};
}
