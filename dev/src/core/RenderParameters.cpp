#include "core_pch.h"
#include "RenderParameters.h"
#include "core/Material.h"
#include "core/MaterialParameter.h"

namespace ld3d
{
	RenderParameters::RenderParameters(void)
	{
		m_clearDepth					= 1.0f;
		m_clearStencil					= 0;
		m_clearClr						= math::Color4(0.0f, 0.2f, 0.3f, 1.0f);
		m_globalAmbientColor			= math::Color4(0.3f, 0.3f, 0.3f, 1.0f);
	}
	
	RenderParameters::~RenderParameters(void)
	{
	}
	void RenderParameters::SetWorldMatrix(const math::Matrix44& world)
	{
		m_matrixBlock.MATRIX_WORLD				= world;
		Update();

	}
	void RenderParameters::SetViewMatrix(const math::Matrix44& view)
	{
		m_matrixBlock.MATRIX_VIEW				= view;
		Update();
	}
	void RenderParameters::SetProjMatrix(const math::Matrix44& proj)
	{
		m_matrixBlock.MATRIX_PROJ				= proj;
		Update();
	}
	void RenderParameters::Update()
	{
		m_matrixBlock.MATRIX_I_WORLD			= math::MatrixInverse(m_matrixBlock.MATRIX_WORLD);
		m_matrixBlock.MATRIX_I_VIEW				= math::MatrixInverse(m_matrixBlock.MATRIX_VIEW);
		m_matrixBlock.MATRIX_I_PROJ				= math::MatrixInverse(m_matrixBlock.MATRIX_PROJ);

		m_matrixBlock.MATRIX_WV					= m_matrixBlock.MATRIX_WORLD * m_matrixBlock.MATRIX_VIEW;
		m_matrixBlock.MATRIX_WVP				= m_matrixBlock.MATRIX_WV * m_matrixBlock.MATRIX_PROJ;

		m_matrixBlock.MATRIX_I_WV				= math::MatrixInverse(m_matrixBlock.MATRIX_WV);	
		m_matrixBlock.MATRIX_I_WVP				= math::MatrixInverse(m_matrixBlock.MATRIX_WVP);
		m_matrixBlock.MATRIX_I_VP				= math::MatrixInverse(m_matrixBlock.MATRIX_VIEW * m_matrixBlock.MATRIX_PROJ);
	}
	const math::Matrix44& RenderParameters::GetWorldMatrix() const
	{
		return m_matrixBlock.MATRIX_WORLD;
	}
	const math::Matrix44& RenderParameters::GetViewMatrix() const
	{
		return m_matrixBlock.MATRIX_VIEW;
	}
	const math::Matrix44& RenderParameters::GetProjMatrix() const
	{
		return m_matrixBlock.MATRIX_PROJ;
	}
	const RenderParameters::MATRIX_BLOCK& RenderParameters::GetMatrixBlock() const
	{
		return m_matrixBlock;
	}
	void RenderParameters::SetClearColor(const math::Color4& clr)
	{
		m_clearClr = clr;
	}
	const math::Color4& RenderParameters::GetClearColor() const
	{
		return m_clearClr;
	}
	void RenderParameters::SetClearDepth(float d)
	{
		m_clearDepth = d;
	}
	float RenderParameters::GetClearDepth() const
	{
		return m_clearDepth;
	}

	void RenderParameters::SetClearStencil(int s)
	{
		m_clearStencil = s;
	}
	int	RenderParameters::GetClearStencil() const
	{
		return m_clearStencil;
	}
	void RenderParameters::SetGlobalAmbientColor(const math::Color4& clr)
	{
		m_globalAmbientColor = clr;
	}
	const math::Color4& RenderParameters::GetGlobalAmbientColor() const
	{
		return m_globalAmbientColor;
	}

	void RenderParameters::SetMaterialMatrixBlock(MaterialPtr pMaterial)
	{
		MaterialParameterPtr pParam = pMaterial->GetParameterByName("_MATRIX");
		if(pParam)
		{
			pParam->SetParameterBlock(&m_matrixBlock, sizeof(MATRIX_BLOCK));
		}
	}
	void RenderParameters::SetMaterialMatrixBlock(MaterialPtr pMaterial, const math::Matrix44& world)
	{
		SetWorldMatrix(world);
		SetMaterialMatrixBlock(pMaterial);
	}
}

