#pragma once


namespace ld3d
{
	class OGL4Loader
	{
	public:
		OGL4Loader(void);
		virtual ~OGL4Loader(void);

		bool										Load();
		void										Unload();
	};
}