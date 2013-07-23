#pragma once

#include "core\ViewFrustum.h"

namespace ld3d
{
	class EXPORT_CLASS RenderData2
	{
	public:
		RenderData2(void)
		{
			dr						= false;
			base_vertex				= 0;
			vertex_count			= 0;
			index_count				= 0;
			start_index				= 0;
			world_matrix.MakeIdentity();
		}

		virtual ~RenderData2(void){}

		GeometryDataPtr											geometry;
		Material2Ptr											material;
		math::Matrix44											world_matrix;
		bool													dr;


		int														base_vertex;
		int														vertex_count;
		int														index_count;
		int														start_index;

		std::function<void (RenderManagerPtr)>					fr_draw;
		std::function<void (RenderManagerPtr)>					dr_draw;
	};
}
