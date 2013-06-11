#pragma once

namespace ld3d
{
	class DT_CoreApi
	{
	public:

		virtual void										Inspector_SetPropertyVisible(const std::wstring& set, const std::wstring& name, bool visible)							= 0;
		virtual void										Inspector_AdjustLayout()																								= 0;


	protected:
		DT_CoreApi(void){}

		virtual ~DT_CoreApi(void){}
	};


}