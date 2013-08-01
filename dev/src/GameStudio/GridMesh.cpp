#include "stdafx.h"
#include "GridMesh.h"




GridMesh::GridMesh(void)
{
}


GridMesh::~GridMesh(void)
{
}
bool GridMesh::Init(ld3d::CoreApiPtr pCore, int size, int grid_size)
{
	using namespace ld3d;

	m_pRD = std::make_shared<RenderData>();


	m_pCore = pCore;
	m_size = size;
	m_gridSize = grid_size;
	
	Sys_GraphicsPtr pGraphics =pCore->GetSysGraphics();
	
	RenderManagerPtr pRenderManager = pCore->GetRenderManager();

	GPUBufferPtr pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * ((size / grid_size + 1) * 4), NULL, true);

	math::Vector3* pBuffer = (math::Vector3*)pVB->Map(MAP_DISCARD);

	math::Vector3* pBufferData = pBuffer;

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2 + grid_size * i;
		vertex->y = 0;
		vertex->z = size/2;
	}

	pBuffer += (size / grid_size + 1);
	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2 + grid_size * i;
		vertex->y = 0;
		vertex->z = -size/2;
	}
	pBuffer += (size / grid_size + 1);



	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2;
		vertex->y = 0;
		vertex->z = size/2 - grid_size * i;
	}
	pBuffer += (size / grid_size + 1);


	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = size/2;
		vertex->y = 0;
		vertex->z = size/2 - grid_size * i;
	}
		
	pVB->Unmap();


	int line_count = (size / grid_size + 1) + (size / grid_size + 1) ;
	int index_count = line_count * 2;
	GPUBufferPtr pIB = pGraphics->CreateBuffer(BT_INDEX_BUFFER, index_count * sizeof(int), NULL, true);

	int * pStart = (int*)pIB->Map(MAP_DISCARD);

	int * pData = pStart;

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		*(pStart + 2* i) = i;
		*(pStart + 2* i + 1) = i + size / grid_size + 1;
	}

	pStart += 2 * (size / grid_size + 1);
	for(int i = 0; i < (size / grid_size + 1) ; ++i)
	{
		*(pStart + 2* i) = i + 2 * (size / grid_size + 1);
		*(pStart + 2* i + 1) = i + size / grid_size + 1 + 2 * (size / grid_size + 1);
	}
	
	pIB->Unmap();

	m_pRD->material = pRenderManager->CreateMaterialFromFile("./assets/standard/material/editor_grid.material");
	m_pRD->geometry = pRenderManager->CreateGeometryData();
	
	VertexLayout layout;
	layout.AddAttribute(G_FORMAT_R32G32B32_FLOAT);

	m_pRD->geometry->BeginGeometry(PT_LINE_LIST);
	{
		m_pRD->geometry->AttachIndexBuffer(pIB, G_FORMAT_R32_UINT);
		m_pRD->geometry->AttachVertexBuffer(pVB, layout);
	}
	m_pRD->geometry->EndGeometry();
	m_pRD->index_count = index_count;

	return true;
}
void GridMesh::Release()
{
	m_pRD->geometry->Release();
	m_pRD->material->Release();
}



math::Matrix44 GridMesh::GetWorldMatrix()
{
	math::Matrix44 mat;
	mat.MakeIdentity();
	return mat;
	
}

bool GridMesh::IsDeferred()
{
	return false;
}

ld3d::RenderDataPtr GridMesh::GetRenderData()
{
	return m_pRD;
}