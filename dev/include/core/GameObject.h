#pragma once

#include <boost/enable_shared_from_this.hpp>
namespace ld3d
{
	class _DLL_CLASS GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(const std::string& name);
		GameObject();
		virtual ~GameObject(void);
		

		bool										IsAncestor(GameObjectPtr pObj);
		void										Update(float dt);
		bool										AddComponent(GameObjectComponentPtr pCom);
		void										RemoveComponent(GameObjectComponentPtr pCom);
		void										RemoveComponent(int index);
		GameObjectComponentPtr						GetComponent(const std::string& name);
		int											GetComponentCount();
		GameObjectComponentPtr						GetComponent(int index);

		GameObjectPtr								ThisPtr();

		void										ClearComponents();
		void										Clear();

		// local transform operation
		void										SetLocalTransform(const math::Matrix44& Local);
		const math::Matrix44&						GetLocalTransform() const;
		math::Matrix44*								GetLocalTransformPtr();
		// translation
		void										SetTranslation(const math::Vector3& t);
		void										SetTranslation(Real x, Real y, Real z);

		void										Translate(const math::Vector3& t);
		void										Translate(Real x, Real y, Real z);

		math::Vector3								GetTranslation() const;

		// rotation
		void										SetRotationAxis(const math::Vector3& axis, Real rad);
		void										SetRotationAxisX(Real rad);
		void										SetRotationAxisY(Real rad);
		void										SetRotationAxisZ(Real rad);
		void										SetRotation(const math::Quat& r);
		void										SetRotation(const math::Matrix44& rot);

		void										Rotate(const math::Quat& r);
		void										Rotate(const math::Matrix44& rot);
		void										RotateAxis(const math::Vector3& axis, Real rad);
		void										RotateAxisX(Real rad);
		void										RotateAxisY(Real rad);
		void										RotateAxisZ(Real rad);

		math::Quat									GetRotation() const;

		// scale
		void										SetScale(const math::Vector3& s);
		void										SetScale(Real x, Real y, Real z);
		math::Vector3								GetScale() const;
		void										SetUnitformScale(Real s);

		void										LookAt(GameObjectPtr pObj);
		void										LookAt(const math::Vector3& at);

		// parent/child operation
		void										LinkTo(GameObjectPtr pParent);
		void										UnLink();
		GameObjectPtr								GetFirstChild();

		GameObjectPtr								GetParent();
		bool										IsRoot();
		GameObjectPtr								GetPrevNode();
		GameObjectPtr								GetNextNode();
		void										SetPrevNode(GameObjectPtr pNode);
		void										SetNextNode(GameObjectPtr pNode);

		std::string*								GetNamePtr();
		const std::string&							GetName() const;
		void										SetName(const std::string& name);
		// world transform operation
		const math::Matrix44&						GetWorldTransform();

		void*										GetPrivateData();
		void										SetPrivateData(void* pData);

		GameObjectPtr								Root();

		GameObjectPtr								Clone();

		EventDispatcherPtr							GetDeventDispatcher();

		EventHandlerID								AddEventHandler(uint32 e, EventHandler handler);
		void										RemoveEventHandler(EventHandlerID id);

		GameObjectPtr								FindChild(const std::string& name);
		GameObjectPtr								FindChildRecursive(const std::string& name);
	private:
		void										UpdateWorldTransform();
		void										UpdateComponents(float dt);

		
	private:
		math::Matrix44								m_LocalTransform;
		math::Matrix44								m_WorldTransform;

		GameObjectPtr								m_pParent;
		GameObjectPtr								m_pFirstChild;

		GameObjectPtr								m_pNext;
		GameObjectPtr								m_pPrev;

		std::vector<GameObjectComponentPtr>			m_components;

		std::string									m_name;

		void*										m_pPrivateData;

		EventDispatcherPtr							m_pEventDispather;

		
	};
}
