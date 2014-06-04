#pragma once

namespace ld3d
{
	class WebpageRenderer
	{
	public:

		WebpageRenderer(void){}

		virtual ~WebpageRenderer(void){}

		virtual void										SetRenderTarget(TexturePtr pTarget)													= 0;
		virtual void										Release()																			= 0;
		virtual void										SetVisible(bool visible)															= 0;
		virtual void										LoadPage(const std::string& url)													= 0;
		virtual void										SetScreenCoord(int x, int y)														= 0;
		virtual void										ExecuteJS(const std::string& code)													= 0;
		virtual void										RegisterScriptCallHandler(const std::string& call_name, 
																const std::function<void(const std::string&)>& handler)							= 0;
	};
}
