// cef_sub_process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>


#include "RenderProcessApp.h"



int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CefMainArgs main_args(hInstance);

	

	return CefExecuteProcess(main_args, new RenderProcessApp);
}
