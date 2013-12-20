#pragma once

#include "cef3/include/cef_app.h"

class ProcessApp : public CefApp, public CefBrowserProcessHandler,
	public CefRenderProcessHandler
{
public:
	ProcessApp(void);
	virtual ~ProcessApp(void);

	// CefApp methods. Important to return |this| for the handler callbacks.
	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line) {
			// Programmatically configure command-line arguments...
	}
	virtual void OnRegisterCustomSchemes(
		CefRefPtr<CefSchemeRegistrar> registrar) OVERRIDE {
			// Register custom schemes...
	}
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE { return this; }
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
		OVERRIDE { return this; }

	// CefBrowserProcessHandler methods.
	virtual void OnContextInitialized() OVERRIDE {
		// The browser process UI thread has been initialized...
	}
	virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info)
		OVERRIDE {
			// Send startup information to a new render process...
	}

	// CefRenderProcessHandler methods.
	virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info)
		OVERRIDE {
			// The render process main thread has been initialized...
			// Receive startup information in the new render process...
	}
	//virtual void OnWebKitInitialized(CefRefPtr<ProcessApp> app) OVERRIDE {
	//	// WebKit has been initialized, register V8 extensions...
	//}
	virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) OVERRIDE {
		// Browser created in this render process...
	}
	virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) OVERRIDE {
		// Browser destroyed in this render process...
	}
	virtual bool OnBeforeNavigation(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		NavigationType navigation_type,
		bool is_redirect) OVERRIDE {
			// Allow or block different types of navigation...
			return true;
	}
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) OVERRIDE {
			// JavaScript context created, add V8 bindings here...
	}
	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) OVERRIDE {
			// JavaScript context released, release V8 references here...
	}
	virtual bool OnProcessMessageReceived(
		CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) OVERRIDE {
			// Handle IPC messages from the browser process...

			return true;
	}

	IMPLEMENT_REFCOUNTING(ProcessApp);
};

