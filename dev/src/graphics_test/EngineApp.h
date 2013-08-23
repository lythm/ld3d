#pragma once


#include "WinApp.h"
#include "core/core_ptr.h"
#include "core/Sys_Graphics.h"

#include <memory>
#include <string>
#include <functional>

namespace ld3d
{
	void _log(const std::string& str);

	class EngineApp : public WinApp
	{
	public:

		template<typename Sys>
		struct Sys_Mod_T
		{
			typedef Sys*					(*Fn_CreateSys)(const std::function<void (const std::string& log)>& logger);
			typedef void					(*Fn_DestroySys)(Sys*);

			std::shared_ptr<Sys>			pSys;

			void*							hLib;
			std::string						filename;


			bool							load_sys(const char* file)
			{
				hLib = os_load_module(file);
				if(hLib == NULL)
				{
					return false;
				}


				Fn_CreateSys CreateSys = (Fn_CreateSys)os_find_proc(hLib, "CreateSys");
				if(CreateSys == NULL)
				{
					os_unload_module(hLib);
					return false;
				}

				filename = file;
				pSys = std::shared_ptr<Sys>(CreateSys(_log), std::bind(&Sys_Mod_T<Sys>::delete_sys, this, std::placeholders::_1));



				return pSys;
			}

			void							delete_sys(Sys* pSys)
			{

				if(hLib == NULL)
				{
					return;
				}
				Fn_DestroySys DestroySys = (Fn_DestroySys)os_find_proc(hLib, "DestroySys");

				if(DestroySys == NULL)
				{
					return;

				}

				DestroySys(pSys);

				os_unload_module(hLib);
				hLib = NULL;
			}
		};

		typedef Sys_Mod_T<Sys_Graphics>				Sys_GraphicsMod;


		EngineApp(void);
		virtual ~EngineApp(void);

		void											OnUpdate();
		bool											OnInit();
		void											OnRelease();


		GeometryDataPtr									CreateCube(float size);

	private:
		
		void											ShowFPS();

		void											HandleMessage(MSG& msg);
	private:

		Sys_GraphicsMod									m_mod;
		Sys_GraphicsPtr								m_pGraphics;

		GeometryDataPtr									m_pGeometry;

		TexturePtr										m_pTex;

		RenderTexturePtr								m_pRenderTarget;

		MaterialPtr									m_pMaterial;
	};
}
