#include "core_pch.h"
#include "core/GameObjectComponent.h"
#include "core_utils.h"
#include "core/DataStream.h"

namespace ld3d
{
	GameObjectComponent::GameObjectComponent(const std::string& name, GameObjectManagerPtr pManager)
	{
		SetName(name);	
		m_pManager = pManager;
		m_bExclusive = true;

		m_pPropertySet = alloc_object<PropertySet>(name);
	}
	GameObjectComponent::GameObjectComponent(GameObjectManagerPtr pManager)
	{
		m_pManager = pManager;
	}

	GameObjectComponent::~GameObjectComponent(void)
	{
		m_pPropertySet.reset();
		m_pObject.reset();
		m_name = "";
	}
	void GameObjectComponent::Update(float dt)
	{

	}
	bool GameObjectComponent::Attach(GameObjectPtr pObject)
	{
		m_pObject = pObject;

		return OnAttach();
	}
	void GameObjectComponent::Detach()
	{
		OnDetach();
		ClearPropertySet();
		m_pObject.reset();
		m_pManager.reset();
	}
	const std::string& GameObjectComponent::GetName()
	{
		return m_name;
	}
	bool GameObjectComponent::OnAttach()
	{
		return true;
	}
	void GameObjectComponent::OnDetach()
	{
	}
	void GameObjectComponent::SetName(const std::string& name)
	{
		m_name = name;
	}
	GameObjectPtr GameObjectComponent::GetGameObject()
	{
		return m_pObject;
	}
	
	bool GameObjectComponent::Serialize(DataStream* pStream)
	{
		const Version& v = GetVersion();
		pStream->WriteInt32(v.AsUInt32());

		return OnSerialize(pStream);
	}
	bool GameObjectComponent::UnSerialize(DataStream* pStream)
	{
		uint32 v = pStream->ReadInt32();

		return OnUnSerialize(pStream, Version(v));
	}
	bool GameObjectComponent::OnSerialize(DataStream* pStream)
	{
		return true;
	}
	bool GameObjectComponent::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		return true;
	}
	GameObjectComponentPtr GameObjectComponent::Clone()
	{
		GameObjectComponentPtr pClone = alloc_object<GameObjectComponent, std::string, GameObjectManagerPtr>(m_name, m_pManager);

		pClone->m_bExclusive = m_bExclusive;

		return pClone;
	}
	
	bool GameObjectComponent::IsExclusive()
	{
		return m_bExclusive;
	}
	void GameObjectComponent::SetExclusive(bool v)
	{
		m_bExclusive = v;
	}
	const Version& GameObjectComponent::GetVersion() const
	{
		return m_version;
	}
	void GameObjectComponent::SetVersion(const Version& v)
	{
		m_version = v;
	}
	PropertySetPtr GameObjectComponent::GetPropertySet()
	{
		return m_pPropertySet;
	}
	void GameObjectComponent::ClearPropertySet()
	{
		m_pPropertySet->clearProperties();
	}
}

