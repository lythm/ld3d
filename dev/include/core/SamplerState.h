#pragma once

namespace ld3d
{
	class SamplerState
	{
	public:

		enum ADDRESS_MODE
		{
			AM_REPEAT,
			AM_MIRROR,
			AM_CLAMP,
			AM_BORDER,
		};

		enum FILTER
		{
			FILTER_MIN_MAG_MIP_POINT,
			FILTER_MIN_MAG_POINT_MIP_LINEAR,
			FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			FILTER_MIN_POINT_MAG_MIP_LINEAR,
			FILTER_MIN_LINEAR_MAG_MIP_POINT,
			FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			FILTER_MIN_MAG_LINEAR_MIP_POINT,
			FILTER_MIN_MAG_MIP_LINEAR,
			FILTER_ANISOTROPIC,
		};


		enum COMPARE_FUNC
		{
			CF_LEQUAL,
			CF_GEQUAL,
			CF_LESS,
			CF_GREATER,
			CF_EQUAL,
			CF_NOTEQUAL,
			CF_ALWAYS,
			CF_NEVER,
		};

		virtual void										SetCompareFunction(COMPARE_FUNC value)																		= 0;

		virtual void										SetLod(float minLod, float maxLod)																			= 0;
		virtual void										SetMipLodBias(int bias)																						= 0;
		virtual void										SetBorderColor(const math::Color4& clr)																		= 0;

		virtual void										SetFilter(FILTER f)																							= 0;

		virtual void										SetAddressMode(ADDRESS_MODE u, ADDRESS_MODE v, ADDRESS_MODE w)												= 0;

		virtual void										SetMaxAnisotropy(uint32 value)																				= 0;
		virtual void										Release()																									= 0;

	protected:
		SamplerState(void){}
		virtual ~SamplerState(void){}
	};


}