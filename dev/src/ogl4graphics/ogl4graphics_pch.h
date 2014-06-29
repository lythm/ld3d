#pragma once


#include <platform/platform.h>

#include "math/math_all.h"


#include "core/core_ptr.h"

#include "utils/logger.h"
#include "utils/utils_helper.h"
#include "utils/Version.h"
#include "utils/scope_exit.h"
#include <vector>

#include "core/g_format.h"

#include "gl_def.h"




namespace ld3d
{
	class OGL4Buffer;
	class OGL4Loader;
	class OGL4RenderWindow;
	class OGL4RenderTexture;
	class OGL4Shader;
	class OGL4Texture;
	class OGL4ShaderProgram;
	class OGL4GeometryData;
	class OGL4RenderState;
	class OGL4Sampler;
	class OGL4DepthStencilBuffer;


	typedef std::shared_ptr<OGL4DepthStencilBuffer>							OGL4DepthStencilBufferPtr;
	typedef std::shared_ptr<OGL4Sampler>									OGL4SamplerPtr;

	typedef std::shared_ptr<OGL4RenderState>								OGL4RenderStatePtr;
	typedef std::shared_ptr<OGL4GeometryData>								OGL4GeometryDataPtr;
	typedef std::shared_ptr<OGL4ShaderProgram>								OGL4ShaderProgramPtr;
	typedef std::shared_ptr<OGL4Shader>										OGL4ShaderPtr;

	typedef std::shared_ptr<OGL4Texture>									OGL4TexturePtr;

	typedef std::shared_ptr<OGL4RenderTexture>								OGL4RenderTexturePtr;
	typedef std::shared_ptr<OGL4Buffer>										OGL4BufferPtr;
	typedef std::shared_ptr<OGL4RenderWindow>								OGL4RenderWindowPtr;
	typedef std::shared_ptr<OGL4Loader>										OGL4LoaderPtr;


	extern Logger&																	logger();
}
