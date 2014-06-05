#include "core_pch.h"
#include "core/DebugPanel.h"
#include "core/HtmlOverlay.h"
#include "core/UIManager.h"
#include "core/CoreApi.h"
#include "core/RenderManager.h"
#include "core/Event.h"
#include "core/WebpageRenderer.h"

#include "core_utils.h"
namespace ld3d
{
	DebugPanel::DebugPanel(void)
	{
		m_updateDeltaTime = 0;
	}


	DebugPanel::~DebugPanel(void)
	{
	}
	bool DebugPanel::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		int w = m_pCore->GetRenderManager()->GetFrameBufferWidth();
		int h = m_pCore->GetRenderManager()->GetFrameBufferHeight();


		m_pOverlay = m_pCore->GetUIManager()->CreateHtmlOverlay("sys_debug_panel", math::RectI(0, 0, w, h / 2), "file:///assets/standard/gui/debug_panel/index.html");

		m_pOverlay->SetZOrder(-2);

		return true;
	}
	void DebugPanel::Release()
	{
		_release_and_reset(m_pOverlay);
		m_pCore.reset();

	}
	void DebugPanel::Show(bool show)
	{
		m_pOverlay->Show(show);
	}
	void DebugPanel::Update(float dt)
	{
		if(m_pOverlay->IsVisible() == false)
		{
			return;
		}
		m_updateDeltaTime += dt;

		if(m_updateDeltaTime < 0.5f)
		{
			return;
		}

		m_updateDeltaTime = 0;
		float avg = m_pCore->GetFrameMetric().GetAvgFPS();
		float fps = m_pCore->GetFrameMetric().GetFPS();

		std::stringstream str;

		str.precision(3);
		str.setf( std::ios::fixed, std:: ios::floatfield );
		str << "fps: "
			<< fps
			<< ", "
			<< 1000.0f / fps
			<< "ms"
			<< " avg_fps: "
			<< avg
			<< ", "
			<< 1000.0f / avg
			<< "ms";

		std::string content = str.str();
		m_pOverlay->GetWebpageRenderer()->ExecuteJS("set_fps('" +  content  + "');");

	}
}
