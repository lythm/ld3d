#include "core_pch.h"
#include "core/DebugPanel.h"
#include "core/HtmlOverlay.h"
#include "core/UIManager.h"
#include "core/CoreApi.h"
#include "core/RenderManager.h"
#include "core/Event.h"
#include "core/WebpageRenderer.h"
#include "core/Allocator.h"

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

		m_pCore->AddEventHandler(EV_RESIZE_FRAMEBUFFER, std::bind(&DebugPanel::_on_resize, this, std::placeholders::_1));
		m_pCore->AddEventHandler(EV_END_FRAME, std::bind(&DebugPanel::_on_end_frame, this, std::placeholders::_1));

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
	
	void DebugPanel::AppendLines(std::stringstream& steam)
	{
		for(int i = 0; i < m_lines.size(); ++i)
		{
			steam << m_lines[i] << "<br>";
		}
	}
	void DebugPanel::AppendFPS(std::stringstream& stream)
	{
		float avg = m_pCore->GetFrameMetric().GetAvgFPS();
		float fps = m_pCore->GetFrameMetric().GetFPS();

		stream << "fps: "
			<< fps
			<< ", "
			<< 1000.0f / fps
			<< "ms"
			<< " avg_fps: "
			<< avg
			<< ", "
			<< 1000.0f / avg
			<< "ms"
			<< "<br>";

	}
	void DebugPanel::AppendMemPool(std::stringstream& stream)
	{
		uint32 total	= m_pCore->GetAllocator()->GetTotalBytes();
		uint32 free		= m_pCore->GetAllocator()->GetBytesLeft();
		stream << "[mempool] "
			<< "total: " 
			<< total
			<< "(" << float(total) / float(1024 * 1024) <<"M)"
			<< " free: "
			<< free
			<< "(" << float(free) / float(1024 * 1024) <<"M)"
			<< " allocated: "
			<< total - free
			<< "(" << float(total - free) / float(1024 * 1024) <<"M)"
			<< "<br>";
	}
	void DebugPanel::_on_resize(EventPtr pEvent)
	{
		Event_ResizeFrameBuffer* pResize = (Event_ResizeFrameBuffer*)pEvent.get();
		
		m_pOverlay->Resize(pResize->w, pResize->h / 2);
	}
	std::string* DebugPanel::AddLine()
	{
		m_lines.push_back("");

		return &m_lines[m_lines.size() - 1];
	}
	void DebugPanel::_on_end_frame(EventPtr pEvent)
	{
		if(m_pOverlay->IsVisible() == false)
		{
			return;
		}

		std::shared_ptr<Event_EndFrame> pEnd = std::dynamic_pointer_cast<Event_EndFrame>(pEvent);

		float dt = pEnd->dt;
		
		m_updateDeltaTime += dt;

		if(m_updateDeltaTime < 0.1f)
		{
			return;
		}

		m_updateDeltaTime = 0;
	
		std::stringstream str;

		str.precision(3);
		str.setf( std::ios::fixed, std:: ios::floatfield );

		AppendFPS(str);
		AppendMemPool(str);
		AppendLines(str);
		std::string content = str.str();
		m_pOverlay->GetWebpageRenderer()->ExecuteJS("set_content('" +  content  + "');");
	}
}
