#include "stdafx.h"
#include "GameScene.h"
#include "GameEngine.h"

GameScene::GameScene(GameEnginePtr pEngine)
{
	m_pEngine = pEngine;

	m_pCore = m_pEngine->GetCoreApi();
	
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
bool GameScene::Save()
{
	if(m_filepath.empty())
	{
		return false;
	}
	return Save(m_filepath);
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
	
}

void GameScene::AddDefaultLight()
{
	using namespace ld3d;
	using namespace ld3d;

	GameObjectPtr pObj = m_pEngine->CreateObjectFromTpl(L"Default Light", L"SkyLight");
	pObj->SetTranslation(1, 1, 1);
	pObj->LookAt(math::Vector3(0, 0, 0));

}

ld3d::GameObjectPtr GameScene::Root()
{
	return m_pEngine->RootObject();
}

