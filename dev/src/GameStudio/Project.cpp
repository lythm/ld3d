#include "stdafx.h"
#include "Project.h"
#include "GameScene.h"
#include "GameEngine.h"
#include "AppContext.h"
#include <QtXml/qdom.h>

Project::Project(GameEnginePtr pEngine)
{
	m_pEngine = pEngine;
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
	
}
bool Project::Save(const boost::filesystem::path& file)
{
	QFile qfile(QString::fromStdString(file.string()));

	SCOPE_EXIT(qfile.close());

	if (!qfile.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QXmlStreamWriter writer(&qfile);
	writer.setAutoFormatting(true);
	writer.setAutoFormattingIndent(-1);

	writer.writeStartDocument();
	{

		writer.writeStartElement("project");
		{
			writer.writeTextElement("scene", QString::fromStdString(m_pScene->GetFileName().string()));

			writer.writeTextElement("clear_color", "0, 0, 0");

			writer.writeStartElement("camera");
			{
				writer.writeTextElement("eye_pos", "0, 0, -100");
				writer.writeTextElement("focus_pos", "0, 0, 0");
			}
			writer.writeEndElement();
		}
		writer.writeEndElement();
	}
	writer.writeEndDocument();


	m_filePath = file;

	RestoreProjectRoot();

	return true;
}
bool Project::Open(const boost::filesystem::path& file)
{
	QFile qfile(QString::fromStdString(file.string()));

	SCOPE_EXIT(qfile.close());

	if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	m_filePath = file;
	RestoreProjectRoot();


	QDomDocument doc;

	if(doc.setContent(&qfile) == false)
	{
		return false;
	}

	QDomNodeList s = doc.elementsByTagName("scene");
	if(s.count() == 0)
	{
		return false;
	}
	QString text = s.at(0).toElement().text();

	m_pScene = alloc_shared<GameScene>(m_pEngine);

	if(text == "")
	{
		if(false == m_pScene->New())
		{
			return false;
		}
	}
	else
	{
		if(false == m_pScene->Load(text.toStdString()))
		{
			return false;
		}
	}

	s = doc.elementsByTagName("camera");
	if(s.count() == 0)
	{
		return false;
	}

	QDomElement e = s.at(0).toElement();

	QDomElement eye = e.firstChildElement("eye_pos");

	QDomElement focus = e.firstChildElement("focus_pos");


	if(eye.isNull() == false)
	{
		math::Vector3 ep;

		QString t = eye.text();

		QString tmp;
		QTextStream stream(&t);
		stream >> ep.x >> tmp >> ep.y >> tmp >> ep.z ;

		//m_pRenderer->GetCamera()->SetEyePos(ep);
	}


	if(focus.isNull() == false)
	{
		math::Vector3 ep;
		QString t = focus.text();
		QString tmp;
		QTextStream stream(&t);
		stream >> ep.x >> tmp >> ep.y >> tmp >> ep.z ;

		//m_pRenderer->GetCamera()->SetFocusPos(fp);
	}


	return true;
}
bool Project::New(const boost::filesystem::path& file)
{
	m_filePath = file;

	boost::filesystem::initial_path();
	RestoreProjectRoot();

	if(false == CreateNewProject(RootPath()))
	{
		return false;
	}

	RestoreProjectRoot();

	m_pScene = alloc_shared<GameScene>(m_pEngine);

	if(false == m_pScene->New())
	{
		return false;
	}

	Save();
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



	if(false == CopyDirectory(init / path("assets"), tar / path("assets")))
	{
		return false;
	}

	if(false == create_directory(tar / path("temp")))
	{
		return false;
	}

	if(false == create_directory(tar / path("packages")))
	{
		return false;
	}

	if(false == create_directory(tar / path("log")))
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
	QString dir = QString::fromStdString(RootPath().string());

	QDir::setCurrent(dir);
}
boost::filesystem::path	Project::RelativeToRoot(const boost::filesystem::path& path)
{
	QDir root(QString::fromStdString(RootPath().string()));

	QString s = root.relativeFilePath(QString::fromStdString(path.string()));

	return s.toStdWString();
}
GameScenePtr Project::GetGameScene()
{
	return m_pScene;
}
bool Project::Save()
{
	return Save(m_filePath);
}

bool Project::HasSceneFileSpecified()
{
	return m_pScene->GetFileName().string() != "";
}

bool Project::NewScene()
{
	m_pScene->Close();
	return m_pScene->New();
}
bool Project::SaveScene()
{
	return m_pScene->Save();
}
bool Project::SaveScene(const boost::filesystem::path& file)
{
	boost::filesystem::path rel = RelativeToRoot(file);
	return m_pScene->Save(rel);
}
bool Project::OpenScene(const boost::filesystem::path& file)
{
	boost::filesystem::path rel = RelativeToRoot(file);
	return m_pScene->Load(rel);
}
boost::filesystem::path Project::GetSceneFilePath()
{
	return RootPath() / m_pScene->GetFileName();
}