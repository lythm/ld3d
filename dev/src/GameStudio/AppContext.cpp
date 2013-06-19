#include "stdafx.h"
#include "AppContext.h"
#include "form_log.h"
#include "Project.h"

Form_Scene*								AppContext::form_scene = nullptr;
Form_Preview*							AppContext::form_preview = nullptr;
ProjectPtr								AppContext::project = nullptr;
Form_Log*								AppContext::form_log = nullptr;
AppContext::AppContext(void)
{
}


AppContext::~AppContext(void)
{
}
void AppContext::log_info(const std::wstring& str)
{
	if(form_log == nullptr)
	{
		return;
	}
	form_log->logInfo(QString::fromStdWString(str));
}
boost::filesystem::path AppContext::project_root()
{
	if(project == nullptr)
	{
		return boost::filesystem::path();
	}

	return project->RootPath();
}