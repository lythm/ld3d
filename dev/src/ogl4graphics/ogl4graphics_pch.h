#pragma once


#include "types\dllexport.h"
#include "types\types.h"

#include "math\math_all.h"


#include "core\core_ptr.h"

#include "utils\utils_all.h"

#include <vector>

#include "core\g_format.h"


namespace ld3d
{

	class OGL4Loader;

	typedef std::shared_ptr<OGL4Loader>										OGL4LoaderPtr;

	void																	g_log(const std::wstring& str);
}
