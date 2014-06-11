#pragma once

#include "core/g_format.h"
#include "core/AppDelegate.h"
#include <vector>

namespace ld3d
{
	struct GraphicsSetting
	{
		GraphicsSetting()
		{
			wnd					= nullptr;
			windowed			= true;
			frameBufferWidth	= 640;
			frameBufferHeight	= 480;
			frameBufferFormat	= G_FORMAT_R8G8B8A8_UNORM;
			depthStencilFormat	= G_FORMAT_D24_UNORM_S8_UINT;
			multiSampleCount	= 1;
			multiSampleQuality	= 0;
			backBufferCount		= 2;
			vsync				= false;
		}
		std::string							sysMod;
		void*								wnd;
		bool								windowed;
		int									frameBufferWidth;
		int									frameBufferHeight;
		G_FORMAT							frameBufferFormat;
		G_FORMAT							depthStencilFormat;
		int									multiSampleCount;
		int									multiSampleQuality;
		int									backBufferCount;
		bool								vsync;
	};

	struct SoundSetting
	{
		SoundSetting()
		{
			maxChannels = 0;
		}
		std::string							sysMod;
		int									maxChannels;
	};
	struct InputSetting
	{
		InputSetting()
		{
			wnd = nullptr;
		}
		std::string							sysMod;
		void*								wnd;
	};
	struct PhysicsSetting
	{
		std::string							sysMod;
	};
	struct NetworkSettting
	{
		std::string							sysMod;
	};
	struct SysSetting
	{
		void*								main_wnd;
		GraphicsSetting						graphics;
		InputSetting						input;
		SoundSetting						sound;
		NetworkSettting						network;
		PhysicsSetting						physics;

		AppDelegate							app_delegate;
		std::vector<std::string>			packages;
		std::string							mod;
	};
}
