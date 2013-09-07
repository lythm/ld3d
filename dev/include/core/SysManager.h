#pragma once

#include "core/CoreApi.h"

namespace ld3d
{
	class _DLL_CLASS SysManager
	{

		template<typename Sys>
		struct Sys_Mod_T
		{
			typedef Sys*					(*Fn_CreateSys)(Logger&);
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
				pSys = std::shared_ptr<Sys>(CreateSys(CoreApi::logger()), boost::bind(&Sys_Mod_T<Sys>::delete_sys, this, _1));



				return pSys != nullptr;
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

		typedef Sys_Mod_T<Sys_Input>			Sys_InputMod;

		typedef Sys_Mod_T<Sys_Graphics>			Sys_GraphicsMod;

		typedef Sys_Mod_T<Sys_Sound>			Sys_SoundMod;

		typedef Sys_Mod_T<Sys_Network>			Sys_NetworkMod;


	public:
		SysManager(void);
		virtual ~SysManager(void);


		bool									Initialize();
		void									Release();

		Sys_GraphicsPtr							LoadSysGraphics(const char* szFile);
		Sys_InputPtr							LoadSysInput(const char* szFile);
		Sys_SoundPtr							LoadSysSound(const char* szFile);
		Sys_NetworkPtr							LoadSysNetwork(const char* szFile);

		Sys_NetworkPtr							GetSys_Network();
		Sys_SoundPtr							GetSys_Sound();
		Sys_InputPtr							GetSysInput();
		Sys_GraphicsPtr							GetSysGraphics();

		void									Update();

	private:

		


	private:

		Sys_GraphicsMod							m_graphicsMod;
		Sys_InputMod							m_inputMod;
		Sys_SoundMod							m_soundMod;
		Sys_NetworkMod							m_networkMod;

	};

}