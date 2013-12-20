// cef_sub_process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cef3/include/cef_app.h"





int _tmain(int argc, _TCHAR* argv[])
{
	CefMainArgs main_args;

	return CefExecuteProcess(main_args, nullptr);
}

