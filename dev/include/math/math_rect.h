#ifndef __MATH_RECT_H__
#define __MATH_RECT_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

namespace math
{
	template <typename T>
	class Rect
	{
	public:
		Rect(void)
		{
			left		= 0;
			top			= 0;
			right		= 0;
			bottom		= 0;
		}
		Rect(T l, T t, T r, T b) : left(l), top(t), right(r), bottom(b)	{}

		~Rect(void)	{}


		T width() const
		{
			return right - left;
		}
		T height() const
		{
			return bottom - top;
		}

		void move(T offset_x, T offset_y)
		{
			left		+= offset_x;
			right		+= offset_x;
			top			+= offset_y;
			bottom		+= offset_y;
		}

		void move_to(T pos_x, T pos_y)
		{
			T offset_x = pos_x - left;
			T offset_y = pos_y - top;

			move(offset_x, offset_y);
		}


		T			left;
		T			top;
		T			right;
		T			bottom;
	};

	typedef Rect<int>		RectI;
	typedef Rect<Real>		RectR;
}
#endif