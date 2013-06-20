#pragma once

namespace ld3d
{
	template <typename F>
	struct scope_exit 
	{
		scope_exit(F f) : f(f) {}
		~scope_exit() { f(); }
		F f;
	};

	template <typename F>
	scope_exit<F> MakeScopeExit(F f) 
	{
		return scope_exit<F>(f);
	};
#define STRING_JOIN2(arg1, arg2) DO_STRING_JOIN2(arg1, arg2)
#define DO_STRING_JOIN2(arg1, arg2) arg1 ## arg2

#define SCOPE_EXIT(code) \
	auto STRING_JOIN2(scope_exit_,__LINE__) = ld3d::MakeScopeExit([&](){code;})
}
