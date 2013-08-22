#include "core_pch.h"
#include "core/SysManager.h"

namespace ld3d
{
	SysManager::SysManager(void)
	{
	}


	SysManager::~SysManager(void)
	{
	}

	Sys_GraphicsPtr	SysManager::LoadSysGraphics(const char* szFile)
	{
		if(m_graphicsMod.load_sys(szFile) == false)
		{
			return Sys_GraphicsPtr();
		}
	
		return m_graphicsMod.pSys;
	}
	Sys_InputPtr SysManager::LoadSysInput(const char* szFile)
	{
		if(m_inputMod.load_sys(szFile) == false)
		{
			return Sys_InputPtr();
		}
		
		return m_inputMod.pSys;

	}

	Sys_InputPtr SysManager::GetSysInput()
	{
		return m_inputMod.pSys;
	}

	Sys_GraphicsPtr	SysManager::GetSysGraphics()
	{
		return m_graphicsMod.pSys;
	}

	Sys_SoundPtr SysManager::LoadSysSound(const char * szFile)
	{
		if(m_soundMod.load_sys(szFile) == false)
		{
			return Sys_SoundPtr();
		}
		return m_soundMod.pSys;
	}
	Sys_SoundPtr SysManager::GetSys_Sound()
	{
		return m_soundMod.pSys;
	}

	Sys_NetworkPtr SysManager::LoadSysNetwork(const char* szFile)
	{
		if(m_networkMod.load_sys(szFile) == false)
		{
			return Sys_NetworkPtr();
		}
		return m_networkMod.pSys;
	}

	Sys_NetworkPtr SysManager::GetSys_Network()
	{
		return m_networkMod.pSys;
	}

	void SysManager::Update()
	{

	}
	bool SysManager::Initialize()
	{
		return true;
	}
	void SysManager::Release()
	{

	}
}
