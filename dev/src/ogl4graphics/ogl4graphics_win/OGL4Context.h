#pragma once

namespace ld3d
{
	class OGL4Context
	{
	public:
		OGL4Context(void);
		virtual ~OGL4Context(void);

		bool									Create();
		void									Release();

	private:

	};

}