#pragma once

namespace ld3d
{
	class _DLL_CLASS Material
	{
		
	public:
		Material(Sys_GraphicsPtr pGraphics);
		virtual ~Material(void);

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

		Sys_GraphicsPtr													m_pGraphics;

		MaterialTechPtr													m_pCurrentTech;
	};
}
