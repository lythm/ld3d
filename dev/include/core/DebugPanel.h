#pragma once

namespace ld3d
{
	class _DLL_CLASS DebugPanel
	{
	public:
		DebugPanel(void);
		virtual ~DebugPanel(void);

		bool									Initialize(CoreApiPtr pCore);
		void									Release();

		void									Show(bool show);

		std::string*							AddLine();

	private:
		void									_on_resize(EventPtr pEvent);
		void									_on_end_frame(EventPtr pEvent);

		void									AppendFPS(std::stringstream& stream);
		void									AppendMemPool(std::stringstream& stream);
		void									AppendLines(std::stringstream& steam);
	private:
		HtmlOverlayPtr							m_pOverlay;
		CoreApiPtr								m_pCore;

		float									m_updateDeltaTime;

		std::vector<std::string>				m_lines;
	};


}