#pragma once

namespace ld3d
{
	namespace voxel
	{
		class Coord
		{
		public:
			Coord(int32 _x, int32 _y, int32 _z)
			{
				x = _x;
				y = _y;
				z = _z;
			}
			Coord(const math::Vector3& v)
			{
				x = (int32)v.x;
				y = (int32)v.y;
				z = (int32)v.z;
			}
			Coord()
			{
				x = 0;
				y = 0;
				z = 0;
			}

			const Coord& operator+=(const Coord& c)
			{
				x += c.x;
				y += c.y;
				z += c.z;
				return *this;
			}

			const Coord& operator-=(const Coord& c)
			{
				x -= c.x;
				y -= c.y;
				z -= c.z;
				return *this;
			}

			const Coord& operator+=(int32 v)
			{
				x += v;
				y += v;
				z += v;
				return *this;
			}

			const Coord& operator-=(int32 v)
			{
				x -= v;
				y -= v;
				z -= v;
				return *this;
			}

			const Coord& operator%=(int32 v)
			{
				x %= v;
				y %= v;
				z %= v;
				return *this;
			}


			Coord operator+() const
			{
				return *this;
			}
			Coord operator-() const
			{
				return Coord(-x, -y, -z);
			}

			const Coord& operator*=(int32 s)
			{
				x *= s;
				y *= s;
				z *= s;

				return *this;
			}

			const Coord& operator/=(int32 s)
			{
				x /= s;
				y /= s;
				z /= s;

				return *this;
			}

			double						Length()
			{
				return sqrt(x * x + y * y + z * z);
			}

			// precision lost
			math::Vector3				ToVector3() const
			{
				return math::Vector3((float)x, (float)y, (float)z);
			}

			int32						x;
			int32						y;
			int32						z;
		};



		inline
			bool operator ==(const Coord& l, const Coord& r)
		{
			return l.x == r.x && l.y == r.y && l.z == r.z;
		}
		inline
			bool operator!=(const Coord& l, const Coord& r)
		{
			return !(l == r);
		}

		inline
			Coord operator+(const Coord& l, const Coord& r)
		{
			return Coord(l.x + r.x, l.y + r.y, l.z + r.z);
		}
		inline
			Coord operator-(const Coord& l, const Coord& r)
		{
			return Coord(l.x - r.x, l.y - r.y, l.z - r.z);
		}

		inline
			Coord operator+(const Coord& l, int32 r)
		{
			return Coord(l.x + r, l.y + r, l.z + r);
		}
		inline
			Coord operator-(const Coord& l, int32 r)
		{
			return l + (-r);
		}


		inline
			Coord operator*(const Coord& l, int32 r)
		{
			return Coord(l.x * r, l.y * r, l.z * r);
		}
		inline
			Coord operator*(int32 l, const Coord& r)
		{
			return Coord(l * r.x, l * r.y, l* r.z);
		}

		inline
			Coord operator/(const Coord& l, int32 r)
		{
			return Coord(l.x / r, l.y / r, l.z / r);
		}
		inline
			Coord operator/(int32 l, const Coord& r)
		{
			return Coord(l / r.x, l / r.y, l / r.z);
		}

		inline
			Coord operator%(const Coord& l, int32 r)
		{
			return Coord(l.x % r, l.y % r, l.z % r);
		}
	}
}

