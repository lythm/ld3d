#pragma once

namespace ld3d
{
	namespace cef
	{
		class CEFManager
		{
		public:
			CEFManager(void);
			virtual ~CEFManager(void);

			bool								Initialize();
			void								Release();

			void								Update();

			CEFWebPagePtr						CreatePage(const std::string& url);
			
		};
	}
}
