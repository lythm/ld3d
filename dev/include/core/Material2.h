#pragma once

namespace ld3d
{
	class Material2
	{
	public:
		Material2(Sys_GraphicsPtr pGraphics);
		virtual ~Material2(void);

		bool											LoadFromFile(const char* szFile);
		void											Release();


		uint32											Begin();
		void											ApplyPass(uint32 index);
		void											End();

		MaterialParameterPtr							GetParameterByName(const char* szName);
		uint32											GetParameterCount();
		MaterialParameterPtr							GetPatameterByIndex(uint32 index);
		
		uint32											GetTechCount();
		MaterialTechPtr									GetTechByIndex(uint32 index);
		MaterialTechPtr									GetTechByName(const char* szName);
		bool											SelectTechByName(const char* szName);


	private:
		std::vector<MaterialTechPtr>					m_techs;
		

		MaterialParameterManagerPtr						m_pParamManager;

		Sys_GraphicsPtr									m_pGraphics;

		MaterialTechPtr									m_pCurrentTech;
	};
}
