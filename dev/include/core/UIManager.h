#pragma once

namespace ld3d
{
	class _DLL_CLASS UIManager
	{
	public:
		UIManager(void);
		virtual ~UIManager(void);

		bool											Initialize();
		void											Release();

		bool											LoadUI(const std::string& src);
		void											Update(float dt);

	};


}
