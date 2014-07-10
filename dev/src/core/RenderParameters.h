#pragma once

namespace ld3d
{
	class RenderParameters
	{
	public:
		struct MATRIX_BLOCK
		{
			math::Matrix44							MATRIX_WORLD;
			math::Matrix44							MATRIX_VIEW;
			math::Matrix44							MATRIX_PROJ;

			math::Matrix44							MATRIX_I_WORLD;
			math::Matrix44							MATRIX_I_VIEW;
			math::Matrix44							MATRIX_I_PROJ;

			math::Matrix44							MATRIX_WV;
			math::Matrix44							MATRIX_WVP;
			
			math::Matrix44							MATRIX_I_WV;
			math::Matrix44							MATRIX_I_WVP;
			math::Matrix44							MATRIX_I_VP;
		};

	public:
		RenderParameters(void);
		virtual ~RenderParameters(void);

		void										SetWorldMatrix(const math::Matrix44& world);
		void										SetViewMatrix(const math::Matrix44& view);
		void										SetProjMatrix(const math::Matrix44& proj);
		void										Update();

		const math::Matrix44&						GetWorldMatrix() const;
		const math::Matrix44&						GetViewMatrix() const;
		const math::Matrix44&						GetProjMatrix() const;


		const MATRIX_BLOCK&							GetMatrixBlock() const;

		void										SetClearColor(const math::Color4& clr);
		const math::Color4&							GetClearColor() const;

		void										SetClearDepth(float d);
		float										GetClearDepth() const;

		void										SetClearStencil(int s);
		int											GetClearStencil() const;

		void										SetGlobalAmbientColor(const math::Color4& clr);
		const math::Color4&							GetGlobalAmbientColor() const;

		void										SetMaterialMatrixBlock(MaterialPtr pMaterial);
		void										SetMaterialMatrixBlock(MaterialPtr pMaterial, const math::Matrix44& world);
	private:
		MATRIX_BLOCK								m_matrixBlock;

		math::Color4								m_clearClr;
		float										m_clearDepth;
		int											m_clearStencil;
		math::Color4								m_globalAmbientColor;
	};


}