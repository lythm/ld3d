#pragma once

namespace ld3d
{
	class CollisionData : public Linked<CollisionData>
	{
	public:

		typedef std::function<void ()>					Event_OnCollide;

		CollisionData(void){}
		virtual ~CollisionData(void){}


		bool											enabled;
		BoundPtr										bound;


		Event_OnCollide									on_collide;								
	};
}

