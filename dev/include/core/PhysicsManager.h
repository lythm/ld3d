#pragma once

namespace ld3d
{
	class PhysicsManager
	{
	public:
		PhysicsManager(void);
		virtual ~PhysicsManager(void);


		bool										Initialize();
		void										Release();
		void										Update(float dt);

		void										AddCollider(ColliderPtr pCollider);
		void										RemoveCollider(ColliderPtr pCollider);

		void										AddCollidee(CollideePtr pCollidee);
		void										RemoveCollidee(CollideePtr pCollidee);

	private:
		ColliderPtr									m_pColliderList;
		CollideePtr									m_pCollideeList;
	};


}
