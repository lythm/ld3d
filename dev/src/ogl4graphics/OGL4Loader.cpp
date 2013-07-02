#include "ogl4graphics_pch.h"
#include "OGL4Loader.h"

//#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace ld3d
{

	OGL4Loader::OGL4Loader(void)
	{
	}


	OGL4Loader::~OGL4Loader(void)
	{
	}
	bool OGL4Loader::Load()
	{
		
		
		int major;
		int minor;
		GLubyte const * str = glGetString(GL_VERSION);
		if (str != NULL)
		{
			std::string const ver(reinterpret_cast<char const *>(str));
			std::string::size_type const pos(ver.find("."));

			major = ver[pos - 1] - '0';
			minor = ver[pos + 1] - '0';
		}
		else
		{
			// GL context has not actived yet
			major = minor = -1;
		}
		return true;
	}
	void OGL4Loader::Unload()
	{

	}
}
