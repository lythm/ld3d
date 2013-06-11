#pragma once

namespace dt
{
	class DT_CoreApiImpl : public ld3d::DT_CoreApi
	{
	public:
		DT_CoreApiImpl(void);
		virtual ~DT_CoreApiImpl(void);


		void										Inspector_SetPropertyVisible(const std::wstring& set, const std::wstring& name, bool visible);
		void										Inspector_AdjustLayout();
		void										RenderView_CaptureInput();
		void										RenderView_ReleaseInput();


	private:
	};


}