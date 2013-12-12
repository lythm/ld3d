#pragma once

#include <functional>

namespace ld3d
{
	struct AppDelegate
	{
		std::function<void (const std::string&)>					SetWindowTitle;
		std::function<void ()>										CenterWindow;
		std::function<void ()>										ExitApp;
		std::function<void (int, int)>								SetWindowSize;
		std::function<void (int&, int&)>							GetWindowSize;
	};
}
