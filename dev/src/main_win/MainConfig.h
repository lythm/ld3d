#pragma once

namespace ld3d
{
	class MainConfig
	{
	public:
		MainConfig(void);
		virtual ~MainConfig(void);

		bool								Load(const std::string& file);
	};

	typedef std::shared_ptr<MainConfig>		MainConfigPtr;
}
