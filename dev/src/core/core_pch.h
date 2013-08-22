#pragma once

#if defined(WIN32) || defined(WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <types/types.h>
#include <types/dllexport.h>

#include <utils/utils_all.h>
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <csignal>
#include <core\core_ptr.h>

#include <vector>
#include <boost\filesystem.hpp>
#include <boost\signal.hpp>

#include <string>
#include <math\math_all.h>

#include <core\g_format.h>

#include <core\property_types.h>
