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
	};


}