#pragma once

class Project
{
public:
	Project(void);
	virtual ~Project(void);


	void								Close();
	void								Save();
	void								Open();
	void								New();
};

