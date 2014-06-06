#pragma once

namespace ld3d
{
	class DebugPanel
	{
	public:
		DebugPanel(void);
		virtual ~DebugPanel(void);

		bool									Initialize(CoreApiPtr pCore);
		void									Release();

		void									Show(bool show);

		void									Update(float dt);

	private:
		void									_on_resize(EventPtr pEvent);

		void									AppendFPS(std::stringstream& stream);
		void									AppendMemPool(std::stringstream& stream);
	private:
		HtmlOverlayPtr							m_pOverlay;
		CoreApiPtr								m_pCore;

		float									m_updateDeltaTime;
	};


}