#pragma once

namespace ld3d
{
	class IntersectionResult
	{
	public:
		enum result
		{
			yes,
			no,
			inside,
			outside,
			invalid,
		};
		IntersectionResult(result r = invalid)
		{
			ret = r;
		}
		

		result													ret;
		math::Vector3											contact_point;
	};
}
