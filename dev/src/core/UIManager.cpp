#include "core_pch.h"
#include "core/UIManager.h"

namespace ld3d
{
	UIManager::UIManager(void)
	{
	}


	UIManager::~UIManager(void)
	{
	}
	bool UIManager::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		return true;
	}
	void UIManager::Release()
	{
	}
	bool UIManager::LoadUI(const std::string& src)
	{
		return true;
	}
	void UIManager::Update(float dt)
	{
		
	}
	void UIManager::_on_key(EventPtr pEvent)
	{
	}
	void UIManager::_on_mouse_move(EventPtr pEvent)
	{
	}
	void UIManager::_on_mouse_button(EventPtr pEvent)
	{
	}
	bool UIManager::DispatchInputEvent(EventPtr pEvent)
	{
		return false;
	}
}
