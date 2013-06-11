#include "stdafx.h"
#include "DT_CoreApiImpl.h"
#include "editor_utils.h"
#include "MainFrm.h"
#include "InspectorProperty.h"

namespace dt
{
	DT_CoreApiImpl::DT_CoreApiImpl(void)
	{
	}


	DT_CoreApiImpl::~DT_CoreApiImpl(void)
	{
	}
	void DT_CoreApiImpl::Inspector_SetPropertyVisible(const std::wstring& set, const std::wstring& name, bool visible)
	{
		CInspectorProperty* pProp = util_get_main_frame()->GetInspector()->FindProperty(set.c_str(), name.c_str());
		if(pProp)
		{
			visible ? pProp->Show() : pProp->Hide();
		}
	}
	void DT_CoreApiImpl::Inspector_AdjustLayout()
	{
		util_get_main_frame()->Inspector_AdjustLayout();
	}
	void DT_CoreApiImpl::RenderView_CaptureInput()
	{
	}
	void DT_CoreApiImpl::RenderView_ReleaseInput()
	{

	}
}