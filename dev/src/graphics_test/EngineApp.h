#pragma once


#include "WinApp.h"
#include "core/core_ptr.h"
#include "core/Sys_Graphics.h"

#include <memory>
#include <string>
#include <functional>

namespace ld3d
{
	void _log(const std::wstring& str);

	class EngineApp : public WinApp
	{
	public:

		template<typename Sys>
		struct Sys_Mod_T
		{
			typedef Sys*					(*Fn_CreateSys)(const std::function<void (const std::wstring& log)>& logger);
			typedef void					(*Fn_DestroySys)(Sys*);

			std::shared_ptr<Sys>			pSys;

			HMODULE							hLib;
			std::wstring					filename;


			bool							load_sys(const wchar_t* file)
			{
				hLib = ::LoadLibrary(file);
				if(hLib == NULL)
				{
					return false;
				}


				Fn_CreateSys CreateSys = (Fn_CreateSys)GetProcAddress(hLib, "CreateSys");
				if(CreateSys == NULL)
				{
					FreeLibrary(hLib);
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
				Fn_DestroySys DestroySys = (Fn_DestroySys)GetProcAddress(hLib, "DestroySys");

				if(DestroySys == NULL)
				{
					return;

				}

				DestroySys(pSys);

				FreeLibrary(hLib);
				hLib = NULL;
			}
		};

		typedef Sys_Mod_T<Sys_Graphics2>				Sys_GraphicsMod;


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
		Sys_Graphics2Ptr								m_pGraphics;

		GeometryDataPtr									m_pGeometry;

		ShaderProgramPtr								m_pProgram;

		Texture2Ptr										m_pTex;

		SamplerStatePtr									m_pSampler;
	};


}
