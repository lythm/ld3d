#pragma once

#include "cef3/include/cef_app.h"

class RenderProcessApp : public CefApp, public CefRenderProcessHandler
{
public:

	class V8Handler : public CefV8Handler
	{
	public:
		V8Handler(CefRefPtr<RenderProcessApp> pApp)
		{
			m_pApp = pApp;
		}
		virtual ~V8Handler()
		{
		}

		bool														Execute(const CefString& name,
																		CefRefPtr<CefV8Value> object,
																		const CefV8ValueList& arguments,
																		CefRefPtr<CefV8Value>& retval,
																		CefString& exception)
		{
			m_pApp->SendCall(arguments.at(0)->GetStringValue(), arguments);
			return true;
		}


		IMPLEMENT_REFCOUNTING(V8Handler);

	private:
		CefRefPtr<RenderProcessApp>									m_pApp;
	};


	RenderProcessApp(void);
	virtual ~RenderProcessApp(void);

	CefRefPtr<CefRenderProcessHandler>								GetRenderProcessHandler();

	void															OnBrowserCreated(CefRefPtr<CefBrowser> browser);
	void															OnBrowserDestroyed(CefRefPtr<CefBrowser> browser);

	bool															OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
																					CefProcessId source_process,
																					CefRefPtr<CefProcessMessage> message);


	void															OnContextCreated(CefRefPtr<CefBrowser> browser,
																					CefRefPtr<CefFrame> frame,
																					CefRefPtr<CefV8Context> context);

	
	void															OnContextReleased(CefRefPtr<CefBrowser> browser,
																					CefRefPtr<CefFrame> frame,
																					CefRefPtr<CefV8Context> context);

	IMPLEMENT_REFCOUNTING(CEFApp);


	void															SendCall(const CefString& name, const CefV8ValueList& arguments);

private:
	CefRefPtr<CefBrowser>											m_pBrowser;

};
