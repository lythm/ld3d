#pragma once

#include "core\BaseMaterial.h"

namespace ld3d
{
	class Material2 : public BaseMaterial
	{
	public:

		class Parameter
		{
		public:
			enum PARAMETER_TYPE
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

			const std::string&									GetName();
			void												SetName(const std::string& name);

			PARAMETER_TYPE										GetType() const;
		private:
			std::string											m_name;
			PARAMETER_TYPE										m_type;
		};

		typedef boost::shared_ptr<Parameter>					ParameterPtr;


		template<typename T>
		class Parameter_T : public Parameter
		{
		public:

		};

		class Pass
		{
		public:
			Pass();
			virtual ~Pass();

		private:
			VertexShaderPtr										m_pVS;
			PixelShaderPtr										m_pPS;
		};


		typedef boost::shared_ptr<Pass>							PassPtr;

		class Tech
		{
		public:
			Tech();
			virtual ~Tech();

		private:
			std::vector<PassPtr>								m_passes;
		};

		
		
		typedef boost::shared_ptr<Tech>							TechPtr;
		


	public:
		Material2(Sys_GraphicsPtr pGraphics);
		virtual ~Material2(void);

		bool									LoadFromFile(const char* szFile);
		void									Release();


		void									Begin();
		void									ApplyPass();
		void									End();

		ParameterPtr							GetParameterByName(const char* szName);
		TechPtr									GetTechByName(const char* szName);

		void									SelectTechByName(const char* szName);



	private:
		std::vector<ParameterPtr>				m_params;
		std::vector<TechPtr>					m_techs;
		



		Sys_GraphicsPtr							m_pGraphics;
	};
}
