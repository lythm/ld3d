#include "stdafx.h"
#include "Project.h"
#include "GameScene.h"
#include "GameEngine.h"


Project::Project(void)
{
}


Project::~Project(void)
{
}
void Project::Close()
{
	if(m_pScene)
	{
		m_pScene->Close();
		m_pScene.reset();
	}
	if(m_pEngine)
	{
		m_pEngine->Release();
		m_pEngine.reset();
	}
	g_Allocator.Release();
}
void Project::Save()
{
}
void Project::Open()
{
}
bool Project::New(const boost::filesystem::path& file)
{
	m_filePath = file;

	g_Allocator.Initialize();
	boost::filesystem::initial_path();
	RestoreProjectRoot();

	if(false == CreateNewProject(RootPath()))
	{
		return false;
	}

	//Save(m_filePath.wstring().c_str());

	RestoreProjectRoot();

	m_pEngine = alloc_shared<GameEngine>();
	if(m_pEngine->Initialize() == false)
	{
		return false;
	}
	m_pScene = alloc_shared<GameScene>(m_pEngine);

	if(false == m_pScene->New())
	{
		return false;
	}

	return true;

}
bool Project::CopyDirectory(boost::filesystem::path src, boost::filesystem::path dst)
{
	namespace fs = boost::filesystem;
	try
	{
		// Check whether the function call is valid
		if( !fs::exists(src) || !fs::is_directory(src))
		{
			return false;
		}
		if(fs::exists(dst))
		{
			return false;
		}
		// Create the destination directory
		if(!fs::create_directory(dst))
		{
			return false;
		}
	}
	catch(fs::filesystem_error const & e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	// Iterate through the source directory
	for(fs::directory_iterator file(src); file != fs::directory_iterator(); ++file)
	{
		try
		{
			fs::path current(file->path());
			if(fs::is_directory(current))
			{
				// Found directory: Recursion
				if(!CopyDirectory(current, dst / current.filename()))
				{
					return false;
				}
			}
			else
			{
				// Found file: Copy
				fs::copy_file(current, dst / current.filename());
			}
		}
		catch(fs::filesystem_error const & e)
		{
			std:: cerr << e.what() << std::endl;
		}
	}
	return true;
}
bool Project::CreateNewProject(const boost::filesystem::path& root)
{
	using namespace boost;
	using namespace filesystem;

	path tar = root;

	path init = initial_path();



	if(false == CopyDirectory(init / path(L"assets"), tar / path(L"assets")))
	{
		return false;
	}

	if(false == create_directory(tar / path(L"temp")))
	{
		return false;
	}

	if(false == create_directory(tar / path(L"packages")))
	{
		return false;
	}

	if(false == create_directory(tar / path(L"log")))
	{
		return false;
	}

	return true;
}
boost::filesystem::path Project::RootPath()
{
	return m_filePath.parent_path();
}
void Project::RestoreProjectRoot()
{
	QString dir = QString::fromStdWString(RootPath().wstring());
	
	QDir::setCurrent(dir);
}
boost::filesystem::path	Project::RelativeToRoot(const boost::filesystem::path& path)
{
	QDir root(QString::fromStdWString(RootPath().wstring()));
	
	QString s = root.relativeFilePath(QString::fromStdWString(path.wstring()));

	return s.toStdWString();
}
