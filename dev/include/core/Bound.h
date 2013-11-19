#pragma once

#include "core/Contact.h"

namespace ld3d
{
	class Bound
	{
	public:

		enum bound_type
		{
			bt_aabb,
			bt_sphere,
			bt_complex,
			bt_unknown,
		};
		
		Bound(bound_type t = bt_unknown, const math::Matrix44& world = math::MatrixIdentity())
		{
			type			= t;
			worldMatrix		= world;
		}

		bound_type														type;

		math::Matrix44													worldMatrix;
	};


	class Bound_Sphere : public Bound
	{
	public:
		
		Bound_Sphere(const math::Sphere& s, const math::Matrix44& world = math::MatrixIdentity()) : Bound(bt_sphere, world)
		{
			sphere = s;
		}

		math::Sphere											sphere;

	};

	class Bound_AABB : public Bound
	{
	public:
		Bound_AABB(const math::AABBox& box, const math::Matrix44& world = math::MatrixIdentity()): Bound(bt_aabb, world)
		{
			aabb = box;
		}
		math::AABBox											aabb;
	};

	class Bound_Complex : public Bound
	{
	public:

		typedef std::function<Contact (BoundPtr)>							FUN_Intersect;
		typedef std::function<Contact (const math::Ray&)>					FUN_RayIntersect;

		Bound_Complex(const math::Matrix44& world = math::MatrixIdentity()) : Bound(bt_complex, world)
		{
		}

		FUN_Intersect														Intersect;
		FUN_RayIntersect													RayIntersect;

	};
}
