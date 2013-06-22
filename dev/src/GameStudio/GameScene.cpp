#include "stdafx.h"
#include "GameScene.h"
#include "GameEngine.h"

GameScene::GameScene(GameEnginePtr pEngine)
{
	m_pEngine = pEngine;

	m_pCore = m_pEngine->GetCoreApi();
	m_objNo	= 0;
}


GameScene::~GameScene(void)
{
}
bool GameScene::New()
{
	m_filepath = L"";

	if(m_pCore->GetRenderManager()->GetLightCount() == 0)
	{
		AddDefaultLight();
	}
	return true;
}

bool GameScene::Load(boost::filesystem::path file)
{

	m_filepath = file;

	using namespace ld3d;

	DataStream_File stream;
	if(false == stream.OpenStream(file.wstring().c_str()))
	{
		return false;
	}

	if(false == m_pCore->GetScene()->UnSerialize(&stream))
	{
		return false;
	}

	stream.Close();

	return true;
}
bool GameScene::Save(boost::filesystem::path file)
{
	m_filepath = file;

	using namespace ld3d;
	DataStream_File stream;
	if(false == stream.OpenStream(file.wstring().c_str(), false))
	{
		return false;
	}

	if(false == m_pCore->GetScene()->Serialize(&stream))
	{
		return false;
	}

	stream.Close();

	return true;
}
const boost::filesystem::path& GameScene::GetFileName()
{
	return m_filepath;
}
void GameScene::Close()
{
	m_filepath = L"";
	if(m_pCore && m_pCore->GetScene())
	{
		m_pCore->GetScene()->Reset();
	}
	m_objNo = 0;
}

void GameScene::AddDefaultLight()
{
	using namespace ld3d;
	using namespace ld3d;

	GameObjectPtr pObj = CreateObjectFromTpl(L"Default Light", L"SkyLight");
	pObj->SetTranslation(1, 1, 1);
	pObj->LookAt(math::Vector3(0, 0, 0));

}
void GameScene::CreateObject_Empty()
{
	using namespace ld3d;
	GameObjectPtr pObj = CreateObject(L"GameObject");
}
ld3d::GameObjectPtr GameScene::CreateObject(const std::wstring& name)
{
	using namespace ld3d;

	QString full_name;

	full_name = QString::fromStdWString(name) + QString("%1").arg(m_objNo);
	

	GameObjectPtr pObj = m_pCore->CreateGameObject(full_name.toStdWString());

	m_objNo++;
	return pObj;
}
ld3d::GameObjectPtr GameScene::CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl)
{
	using namespace ld3d;

	QString full_name;

	full_name = QString::fromStdWString(name) + QString("%1").arg(m_objNo);

	GameObjectPtr pObj = m_pCore->CreatGameObjectFromTemplate(tpl, full_name.toStdWString());

	m_objNo++;
	return pObj;
}
ld3d::GameObjectComponentPtr GameScene::CreateGameObjectComponent(const std::wstring& name)
{
	return m_pCore->CreateGameObjectComponent(name);
}
ld3d::GameObjectPtr GameScene::Root()
{
	if(m_pCore == nullptr)
	{
		return ld3d::GameObjectPtr();
	}
	return m_pCore->Root();
}

