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
		
	private:
		HtmlOverlayPtr							m_pOverlay;
		CoreApiPtr								m_pCore;

		float									m_updateDeltaTime;
	};


}