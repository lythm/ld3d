#pragma once

namespace ld3d
{
	class EXPORT_CLASS Material2
	{
		
	public:
		Material2(Sys_Graphics2Ptr pGraphics);
		virtual ~Material2(void);

		void															Release();

		uint32															Begin();
		void															ApplyPass(uint32 index);
		void															End();

		MaterialParameterPtr											GetParameterByName(const char* szName);
				
		uint32															GetTechCount();
		MaterialTechPtr													GetTechByIndex(uint32 index);
		MaterialTechPtr													GetTechByName(const char* szName);

		bool															SetCurrentTech(const char* szName);

		void															AddTech(MaterialTechPtr pTech);

	private:
		std::vector<MaterialTechPtr>									m_techs;
		
		MaterialParameterManagerPtr										m_pParamManager;

		Sys_Graphics2Ptr												m_pGraphics;

		MaterialTechPtr													m_pCurrentTech;
	};
}
