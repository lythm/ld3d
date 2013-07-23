#pragma once

class GridMesh
{
public:
	GridMesh(void);
	virtual ~GridMesh(void);

	bool									Init(ld3d::CoreApiPtr pCore, int size, int grid_size);
	void									Release();

	math::Matrix44							GetWorldMatrix();

	bool									IsDeferred();

	ld3d::RenderDataPtr					GetRenderData();
private:
	int										m_size;
	int										m_gridSize;
	
	ld3d::CoreApiPtr						m_pCore;
	ld3d::RenderDataPtr					m_pRD;
};

