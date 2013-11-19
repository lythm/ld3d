#pragma once

namespace ld3d
{
	class Contact
	{
	public:
		enum Result
		{
			Yes,
			No,
			Invalid,
		};

		Contact(Result r = Invalid)
		{
			result					= r;
			enter_point				= math::Vector3(0, 0, 0);
			normal					= math::Vector3(0, 0, 0);
			penetration				= 0;
		}

		Result													result;

		math::Vector3											enter_point;
		math::Vector3											normal;
		float													penetration;
	};
}
