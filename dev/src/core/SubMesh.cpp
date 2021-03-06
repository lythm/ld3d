#include "core_pch.h"
#include "core/SubMesh.h"
#include "core/Mesh.h"


namespace ld3d
{
	SubMesh::SubMesh()
	{
		
	}


	SubMesh::~SubMesh(void)
	{
	}
	void SubMesh::Create(MeshPtr pMesh, int indexOffset, int indexCount, int vertexOffset, int vertexCount, int vertexStride, int matIndex, int primCount, PRIMITIVE_TYPE primType, const VertexLayout& vf, G_FORMAT indexFormat)
	{
		m_pMesh						= pMesh;

		m_indexOffset				= indexOffset;
		m_vertexOffset				= vertexOffset;

		m_vertexCount				= vertexCount;
		m_indexCount				= indexCount;
		m_primitiveCount			= primCount;
		m_materialIndex				= matIndex;
		m_vertexStride				= vertexStride;

		m_indexed					= pMesh->GetIndexData() == NULL ? false : true;
		m_primitiveType				= primType;

		m_vertexLayout				= vf;
		m_indexFormat				= indexFormat;
	}
	G_FORMAT SubMesh::GetIndexFormat()
	{
		return m_indexFormat;
	}
	const VertexLayout& SubMesh::GetVertexFormat()
	{
		return m_vertexLayout;
	}
	void* SubMesh::GetIndexData()
	{
		return m_pMesh->GetIndexData();
	}
	void* SubMesh::GetVertexData()
	{
		return m_pMesh->GetVertexData();
	}
	int SubMesh::GetIndexDataOffset()
	{
		return m_indexOffset;
	}
	int SubMesh::GetVertexDataOffset()
	{
		return m_vertexOffset;
	}
	int	SubMesh::GetIndexDataBytes()
	{
		return m_indexCount * GetIndexBytes();
	}
	int SubMesh::GetVertexDataBytes()
	{
		return m_vertexCount * m_vertexStride;
	}
	int SubMesh::GetIndexCount()
	{
		return m_indexCount;
	}
	int	SubMesh::GetVertexCount()
	{
		return m_vertexCount;
	}
	int	SubMesh::GetVertexStride()
	{
		return m_vertexStride;
	}

	MaterialPtr SubMesh::GetMaterial()
	{
		return m_pMesh->GetMaterialByIndex(m_materialIndex);
	}
	int SubMesh::GetPrimitiveCount()
	{
		return m_primitiveCount;
	}
	PRIMITIVE_TYPE SubMesh::GetPrimitiveType()
	{
		return m_primitiveType;
	}
	bool SubMesh::IsIndexed()
	{
		return m_indexed;
	}
	int SubMesh::GetIndexBytes()
	{
		switch(m_indexFormat)
		{
		case G_FORMAT_R32_SINT:
		case G_FORMAT_R32_UINT:
			return sizeof(uint32);
		case G_FORMAT_R16_SINT:
		case G_FORMAT_R16_UINT:
			return sizeof(uint16);
		default:
			break;
		}
		return sizeof(uint32);
	}
}
