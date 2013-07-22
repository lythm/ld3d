#pragma once

#include "core\ViewFrustum.h"

namespace ld3d
{
	class EXPORT_CLASS RenderData
	{
	public:

		RenderData(void){}

		virtual ~RenderData(void){}


		virtual void											Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr())	= 0;
		virtual MaterialPtr										GetMaterial()																= 0;
		virtual math::Matrix44									GetWorldMatrix()															= 0;
		virtual bool											IsDeferred(){return false;}

	};

	class EXPORT_CLASS RenderData2
	{
	public:
		RenderData2(void){}

		virtual ~RenderData2(void){}

		GeometryDataPtr											pGeometry;
		Material2Ptr											pMaterial;
		math::Matrix44											worldMatrix;
		bool													dr;

	};
}
