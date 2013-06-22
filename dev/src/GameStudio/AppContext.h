#pragma once
class Form_Preview;
class Form_Scene;
class Form_Log;

class AppContext
{
public:

	static bool										Initialize();

	static GameEditorPtr							editor;

	static Form_Preview*							form_preview;
	static Form_Scene*								form_scene;
	static ProjectPtr								project;
	static Form_Log*								form_log;

	static void										log_info(const std::wstring& str);
	static boost::filesystem::path					project_root();



	static GameEditorPtr							GameEditor();

private:
	AppContext(void);
	virtual ~AppContext(void);
};

