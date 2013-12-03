#pragma once



//namespace Awesomium
//{
//	class WebCore;
//};


namespace ld3d
{

	class _DLL_CLASS UIManager
	{
	public:
		UIManager(void);
		virtual ~UIManager(void);

		bool											Initialize(CoreApiPtr pCore);
		void											Release();

		bool											LoadUI(const std::string& src);
		void											Update(float dt);

	private:
		void											_on_key(EventPtr pEvent);
		void											_on_mouse_move(EventPtr pEvent);
		void											_on_mouse_button(EventPtr pEvent);

	private:

		CoreApiPtr										m_pCore;

	/*	Awesomium::WebCore*								m_pWebCore;*/
	};


}
