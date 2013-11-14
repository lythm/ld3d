#pragma once

#include "core/SamplerState.h"

namespace ld3d
{
	class OGL4Sampler : public SamplerState
	{
	public:
		OGL4Sampler(void);
		virtual ~OGL4Sampler(void);


		void										Bind(uint32 slot);

		void										SetCompareFunction(TEXTURE_COMPARE_FUNC value);
		void										SetCompareMode(TEXTURE_COMPARE_MODE value);
		void										SetLod(float minLod, float maxLod);
		//void										SetMipLodBias(int bias);
		void										SetBorderColor(const math::Color4& clr);

		void										SetFilter(FILTER f);
		
		void										SetAddressMode(ADDRESS_MODE u, ADDRESS_MODE v, ADDRESS_MODE w);

		void										SetMaxAnisotropy(uint32 value);

		void										Release();

		bool										Create();


		GLuint										GetSamplerObject();


	private:
		GLenum										AddressModeToGL(ADDRESS_MODE mode);
	private:
		GLuint										m_sampler;
	};
}
