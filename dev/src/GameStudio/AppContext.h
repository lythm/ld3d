#pragma once

class Form_Scene;
class AppContext
{
public:



	static Form_Scene*								pSceneForm;
	static ProjectPtr								pProject;

private:
	AppContext(void);
	virtual ~AppContext(void);
};

