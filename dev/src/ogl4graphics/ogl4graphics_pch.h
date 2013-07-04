#pragma once


#include "types\dllexport.h"
#include "types\types.h"

#include "math\math_all.h"


#include "core\core_ptr.h"

#include "utils\utils_all.h"

#include <vector>

#include "core/g_format.h"

#include "gl_def.h"


namespace ld3d
{
	class OGL4Buffer;
	class OGL4Loader;
	class OGL4RenderWindow;
	class OGL4RenderTexture;
	class OGL4ShaderCompiler;
	class OGL4VertexShader;
	class OGL4FragmentShader;
	class OGL4Texture;

	typedef std::shared_ptr<OGL4FragmentShader>								OGL4FragmentShaderPtr;
	typedef std::shared_ptr<OGL4VertexShader>								OGL4VertexShaderPtr;
	typedef std::shared_ptr<OGL4ShaderCompiler>								OGL4ShaderCompilerPtr;

	typedef std::shared_ptr<OGL4Texture>									OGL4TexturePtr;

	typedef std::shared_ptr<OGL4RenderTexture>								OGL4RenderTexturePtr;
	typedef std::shared_ptr<OGL4Buffer>										OGL4BufferPtr;
	typedef std::shared_ptr<OGL4RenderWindow>								OGL4RenderWindowPtr;
	typedef std::shared_ptr<OGL4Loader>										OGL4LoaderPtr;

	void																	g_log(const std::wstring& str);
}
