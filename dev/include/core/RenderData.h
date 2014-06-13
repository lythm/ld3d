#pragma once

//#include "core/ViewFrustum.h"

namespace ld3d
{
	class _DLL_CLASS RenderData
	{
	public:
		RenderData(void)
		{
			base_vertex				= 0;
			vertex_count			= 0;
			index_count				= 0;
			start_index				= 0;
			world_matrix.MakeIdentity();
		}

		virtual ~RenderData(void){}

		GeometryDataPtr											geometry;
		MaterialPtr												material;
		math::Matrix44											world_matrix;

		int														base_vertex;
		int														vertex_count;
		int														index_count;
		int														start_index;

		std::function<void (RenderManagerPtr)>					fr_draw;
		std::function<void (RenderManagerPtr)>					dr_draw;
		std::function<void (RenderManagerPtr, MaterialPtr)>		sm_draw;
	};
}
