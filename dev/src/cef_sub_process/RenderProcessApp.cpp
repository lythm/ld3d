#include "RenderProcessApp.h"
#include "cef3/include/cef_runnable.h"


RenderProcessApp::RenderProcessApp(void)
{
}


RenderProcessApp::~RenderProcessApp(void)
{
}
CefRefPtr<CefRenderProcessHandler> RenderProcessApp::GetRenderProcessHandler()
{
	return this;
}
void RenderProcessApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser)
{
	m_pBrowser = browser;
		
}
void RenderProcessApp::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
	m_pBrowser = nullptr;
}
bool RenderProcessApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
												CefProcessId source_process,
												CefRefPtr<CefProcessMessage> message)
{
	return false;
}
void RenderProcessApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
										CefRefPtr<CefFrame> frame,
										CefRefPtr<CefV8Context> context)
{
	
//	CEF_REQUIRE_RENDERER_THREAD();

	// Register function handlers with the 'window' object.
	CefRefPtr<CefV8Value> window = context->GetGlobal();

	CefRefPtr<V8Handler> handler = new V8Handler(this);
	CefV8Value::PropertyAttribute attributes =
		static_cast<CefV8Value::PropertyAttribute>(
		V8_PROPERTY_ATTRIBUTE_READONLY |
		V8_PROPERTY_ATTRIBUTE_DONTENUM |
		V8_PROPERTY_ATTRIBUTE_DONTDELETE);

	// Add the query function.
	CefRefPtr<CefV8Value> query_func =
		CefV8Value::CreateFunction("script_call", handler.get());
	window->SetValue("script_call", query_func, attributes);
}


void RenderProcessApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
										 CefRefPtr<CefFrame> frame,
										 CefRefPtr<CefV8Context> context)
{

}

void RenderProcessApp::SendCall(const CefString& name, const CefV8ValueList& arguments)
{
	CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("script_call");
	CefRefPtr<CefListValue> args = msg->GetArgumentList();
	args->SetString(0, name);
	args->SetInt(1, arguments.size());
	
	for(int i = 0; i < arguments.size(); ++i)
	{
		CefString arg = arguments.at(i)->GetStringValue();
		args->SetString(2 + i, arg);
	}

	
	m_pBrowser->SendProcessMessage(PID_BROWSER, msg);
}
