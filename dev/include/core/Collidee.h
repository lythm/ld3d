#pragma once
namespace ld3d
{
	class Collidee : public Linked<Collidee>
	{
	public:
		Collidee(void);
		virtual ~Collidee(void);
	};
}
