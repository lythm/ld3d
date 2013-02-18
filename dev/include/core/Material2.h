#pragma once


namespace ld3d
{
	class Material2
	{
	public:

		class Parameter
		{
		public:
			enum
			{
				pt_float,
				pt_float2,
				pt_float3,
				pt_float4,
				pt_float4x4,
				pt_int,
				pt_int2,
				pt_int3,
				pt_int4,
				pt_bool,
				pt_string,
				pt_texture,
				pt_sampler,

			};

			Parameter();
			virtual ~Parameter();

			const std::string&						GetName();
			void									SetName(const std::string& name);

			
		private:
			std::string								m_name;
		};

		template<typename T>
		class Parameter_T : public Parameter
		{
		public:

		};

		class Pass
		{
		};


		class Tech
		{
		public:


		private:
			std::vector<Pass>			m_passes;
		};

		



	public:
		Material2(Sys_GraphicsPtr pGraphics);
		virtual ~Material2(void);

		bool									LoadFromFile(const char* szFile);
		void									Release();


		void									Begin();
		void									ApplyPass();
		void									End();
	private:
		std::vector<Parameter>					m_params;
		std::vector<Tech>						m_techs;
		
		Sys_GraphicsPtr							m_pGraphics;
	};
}
