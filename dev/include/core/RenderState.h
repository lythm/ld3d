#pragma once

namespace ld3d
{
	class RenderState
	{
	public:

		enum RS_BLEND
		{
			RS_BLEND_ZERO               = 1,
			RS_BLEND_ONE                = 2,
			RS_BLEND_SRC_COLOR          = 3,
			RS_BLEND_INV_SRC_COLOR      = 4,
			RS_BLEND_SRC_ALPHA          = 5,
			RS_BLEND_INV_SRC_ALPHA      = 6,
			RS_BLEND_DEST_ALPHA         = 7,
			RS_BLEND_INV_DEST_ALPHA     = 8,
			RS_BLEND_DEST_COLOR         = 9,
			RS_BLEND_INV_DEST_COLOR     = 10,
			RS_BLEND_SRC_ALPHA_SAT      = 11,
			RS_BLEND_BLEND_FACTOR       = 14,
			RS_BLEND_INV_BLEND_FACTOR   = 15,
			RS_BLEND_SRC1_COLOR         = 16,
			RS_BLEND_INV_SRC1_COLOR     = 17,
			RS_BLEND_SRC1_ALPHA         = 18,
			RS_BLEND_INV_SRC1_ALPHA     = 19,
		};

		enum RS_BLEND_OP
		{
			RS_BLEND_OP_ADD            = 1,
			RS_BLEND_OP_SUBTRACT       = 2,
			RS_BLEND_OP_REV_SUBTRACT   = 3,
			RS_BLEND_OP_MIN            = 4,
			RS_BLEND_OP_MAX            = 5,
		};

		enum RS_COLOR_WRITE
		{
			RS_COLOR_WRITE_ENABLE_RED     = 1,
			RS_COLOR_WRITE_ENABLE_GREEN   = 2,
			RS_COLOR_WRITE_ENABLE_BLUE    = 4,
			RS_COLOR_WRITE_ENABLE_ALPHA   = 8,
			RS_COLOR_WRITE_ENABLE_ALL     = (RS_COLOR_WRITE_ENABLE_RED | 
			RS_COLOR_WRITE_ENABLE_GREEN |  
			RS_COLOR_WRITE_ENABLE_BLUE | 
			RS_COLOR_WRITE_ENABLE_ALPHA),
		};

		enum RS_FILL_MODE
		{
			RS_FILL_WIREFRAME   = 2,
			RS_FILL_SOLID       = 3,
		};

		enum RS_CULL_MODE
		{
			RS_CULL_NONE    = 1,
			RS_CULL_FRONT   = 2,
			RS_CULL_BACK    = 3,
		};



		virtual void										Begin()									= 0;

		virtual void										End()									= 0;

		virtual void										Release()								= 0;

	protected:
		RenderState(void){}
		virtual ~RenderState(void){}
	};
}
