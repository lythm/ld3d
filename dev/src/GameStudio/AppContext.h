#pragma once
class Form_Preview;
class Form_Scene;
class Form_Log;
class AppContext
{
public:


	static Form_Preview*							form_preview;
	static Form_Scene*								form_scene;
	static ProjectPtr								project;
	static Form_Log*								form_log;

	static void										log_info(const std::wstring& str);
	static boost::filesystem::path					project_root();
private:
	AppContext(void);
	virtual ~AppContext(void);
};

