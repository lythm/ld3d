// cef_sub_process.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <Windows.h>


#include "cef3/include/cef_app.h"





//int _tmain(int argc, _TCHAR* argv[])
//{
//	CefMainArgs main_args(GetModuleHandle(NULL));
//
//	
//
//	return CefExecuteProcess(main_args, nullptr);
//}

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CefMainArgs main_args(hInstance);

	

	return CefExecuteProcess(main_args, nullptr);
}