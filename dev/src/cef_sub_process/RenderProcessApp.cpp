#include "RenderProcessApp.h"
#include "cef3/include/cef_runnable.h"


static std::string invoke_host_call = "invoke_host_call";
static std::string invoke_script_call = "invoke_script_call";


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
		CefV8Value::CreateFunction(invoke_host_call, handler.get());
	window->SetValue(invoke_host_call, query_func, attributes);
}


void RenderProcessApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
										 CefRefPtr<CefFrame> frame,
										 CefRefPtr<CefV8Context> context)
{

}

void RenderProcessApp::SendCall(const CefString& json)
{
	CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(invoke_host_call);
	CefRefPtr<CefListValue> args = msg->GetArgumentList();

	args->SetString(0, json);
	
	m_pBrowser->SendProcessMessage(PID_BROWSER, msg);
}
