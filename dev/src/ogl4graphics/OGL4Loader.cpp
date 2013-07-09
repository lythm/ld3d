#include "ogl4graphics_pch.h"
#include "OGL4Loader.h"


#include <regex>
#include <algorithm>


#define LOAD_API(name, type)			name = (type)wglGetProcAddress(#name);assert(name != nullptr);

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
		if(false == load_version())
		{
			return false;
		}
		
		if(false == load_extension_info())
		{
			return false;
		}

		if(false == load_api())
		{
			return false;
		}
		return true;
	}
	bool OGL4Loader::load_version()
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

		m_ver = Version(major, minor, 0, 0);

		return true;
	}
	bool OGL4Loader::load_extension_info()
	{
		LOAD_API(glGetStringi, PFNGLGETSTRINGIPROC);

		if(glGetStringi == nullptr)
		{
			return false;
		}
		GLint num_exts;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num_exts);
		for (GLint i = 0; i < num_exts; ++ i)
		{
			const char* szExt = (const char*)glGetStringi(GL_EXTENSIONS, i);

			m_exts.push_back(szExt);
		}

		return true;
	}
	void OGL4Loader::Unload()
	{
		m_exts.clear();
	}
	bool OGL4Loader::IsExtSupported(const std::string& ext)
	{
		return m_exts.end() != std::find(m_exts.begin(), m_exts.end(), ext);
	}
	bool OGL4Loader::load_api()
	{
		LOAD_API(wglSwapIntervalEXT,									PFNWGLSWAPINTERVALEXTPROC);

		LOAD_API(glGetStringi,											PFNGLGETSTRINGIPROC);

		LOAD_API(glGenBuffers,											PFNGLGENBUFFERSPROC);

		LOAD_API(glBindBuffer,											PFNGLBINDBUFFERPROC);
		LOAD_API(glBufferData,											PFNGLBUFFERDATAPROC);


		LOAD_API(glEnableVertexAttribArray,								PFNGLENABLEVERTEXATTRIBARRAYPROC);
		LOAD_API(glDisableVertexAttribArray,							PFNGLDISABLEVERTEXATTRIBARRAYPROC);
		LOAD_API(glIsBuffer,											PFNGLISBUFFERPROC);

		LOAD_API(glBufferSubData,										PFNGLBUFFERSUBDATAPROC);
		LOAD_API(glMapBufferRange,										PFNGLMAPBUFFERRANGEPROC);
		LOAD_API(glUnmapBuffer,											PFNGLUNMAPBUFFERPROC);
		LOAD_API(glDeleteBuffers,										PFNGLDELETEBUFFERSPROC);
		LOAD_API(glBindVertexBuffer,									PFNGLBINDVERTEXBUFFERPROC);
		
		LOAD_API(glVertexAttribPointer,									PFNGLVERTEXATTRIBPOINTERPROC);


		LOAD_API(glClearBufferfv,										PFNGLCLEARBUFFERFVPROC);
		LOAD_API(glClearBufferfi,										PFNGLCLEARBUFFERFIPROC);

		LOAD_API(glDebugMessageControl,									PFNGLDEBUGMESSAGECONTROLPROC);
		LOAD_API(glDebugMessageInsert,									PFNGLDEBUGMESSAGEINSERTPROC);
		LOAD_API(glDebugMessageCallback,								PFNGLDEBUGMESSAGECALLBACKPROC);
		LOAD_API(glGetDebugMessageLog,									PFNGLGETDEBUGMESSAGELOGPROC);


		LOAD_API(glTexImage3D,											PFNGLTEXIMAGE3DPROC);
		LOAD_API(glGenerateMipmap,										PFNGLGENERATEMIPMAPPROC);
		LOAD_API(glActiveTexture,										PFNGLACTIVETEXTUREPROC);


		LOAD_API(glGenVertexArrays,										PFNGLGENVERTEXARRAYSPROC);
		LOAD_API(glBindVertexArray,										PFNGLBINDVERTEXARRAYPROC);
		LOAD_API(glDeleteVertexArrays,									PFNGLDELETEVERTEXARRAYSPROC);


		LOAD_API(glCreateProgram,										PFNGLCREATEPROGRAMPROC);
		LOAD_API(glDeleteProgram,										PFNGLDELETEPROGRAMPROC);
		LOAD_API(glLinkProgram,											PFNGLLINKPROGRAMPROC);
		LOAD_API(glUseProgram,											PFNGLUSEPROGRAMPROC);

		LOAD_API(glCreateShader,										PFNGLCREATESHADERPROC);
		LOAD_API(glDeleteShader,										PFNGLDELETESHADERPROC);
		LOAD_API(glShaderSource,										PFNGLSHADERSOURCEPROC);
		LOAD_API(glCompileShader,										PFNGLCOMPILESHADERPROC);
		LOAD_API(glAttachShader,										PFNGLATTACHSHADERPROC);
		LOAD_API(glDetachShader,										PFNGLDETACHSHADERPROC);


		LOAD_API(glGetProgramiv,										PFNGLGETPROGRAMIVPROC);
		LOAD_API(glGetProgramInfoLog,									PFNGLGETPROGRAMINFOLOGPROC);
		LOAD_API(glValidateProgram,										PFNGLVALIDATEPROGRAMPROC);
		LOAD_API(glGetShaderiv,											PFNGLGETSHADERIVPROC);
		LOAD_API(glGetShaderInfoLog,									PFNGLGETSHADERINFOLOGPROC);

		LOAD_API(glBindBufferRange,										PFNGLBINDBUFFERRANGEPROC);
		LOAD_API(glBindBufferBase,										PFNGLBINDBUFFERBASEPROC);

		LOAD_API(glGetUniformBlockIndex,								PFNGLGETUNIFORMBLOCKINDEXPROC);
		LOAD_API(glUniformBlockBinding,									PFNGLUNIFORMBLOCKBINDINGPROC);

		LOAD_API(glGetActiveUniformBlockiv,								PFNGLGETACTIVEUNIFORMBLOCKIVPROC);
		LOAD_API(glGetActiveUniformBlockName,							PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC);

		LOAD_API(glGetActiveUniformsiv,									PFNGLGETACTIVEUNIFORMSIVPROC);
		LOAD_API(glGetUniformLocation,									PFNGLGETUNIFORMLOCATIONPROC);


		LOAD_API(glProgramUniform1f,									PFNGLPROGRAMUNIFORM1FPROC);
		LOAD_API(glProgramUniform1i,									PFNGLPROGRAMUNIFORM1IPROC);
		LOAD_API(glProgramUniform1ui,									PFNGLPROGRAMUNIFORM1UIPROC);

		LOAD_API(glProgramUniform2fv,									PFNGLPROGRAMUNIFORM2FVPROC);
		LOAD_API(glProgramUniform3fv,									PFNGLPROGRAMUNIFORM3FVPROC);
		LOAD_API(glProgramUniform4fv,									PFNGLPROGRAMUNIFORM4FVPROC);

		LOAD_API(glProgramUniform2iv,									PFNGLPROGRAMUNIFORM2IVPROC);
		LOAD_API(glProgramUniform3iv,									PFNGLPROGRAMUNIFORM3IVPROC);
		LOAD_API(glProgramUniform4iv,									PFNGLPROGRAMUNIFORM4IVPROC);

		LOAD_API(glProgramUniform2uiv,									PFNGLPROGRAMUNIFORM2UIVPROC);
		LOAD_API(glProgramUniform3uiv,									PFNGLPROGRAMUNIFORM3UIVPROC);
		LOAD_API(glProgramUniform4uiv,									PFNGLPROGRAMUNIFORM4UIVPROC);

		LOAD_API(glProgramUniformMatrix4fv,								PFNGLPROGRAMUNIFORMMATRIX4FVPROC);

		return true;
	}
}
