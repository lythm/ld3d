#pragma once


namespace ld3d
{
	class EXPORT_CLASS Mesh
	{
	public:

		Mesh(void);
		virtual ~Mesh(void);

		int											GetIndexDataBytes();
		int											GetVertexDataBytes();
		void*										GetIndexData();
		void*										GetVertexData();
		Material2Ptr								GetMaterialByIndex(int index);
		int											GetMaterialCount();

		bool										Create(int indexBufferSize, void* pIndexBuffer, int vertexBufferSize, void* pVertexBuffer, const std::vector<Material2Ptr>& materialList);
		void										AddSubMesh(SubMeshPtr pSub);

		int											GetSubMeshCount();
		SubMeshPtr									GetSubMesh(int index);
		void										Destroy();
		void										Update();
	private:
		void*										m_pIndexData;
		int											m_indexDataBytes;
		void*										m_pVertexData;
		int											m_vertexDataBytes;
		
		std::vector<Material2Ptr>					m_materialList;
		std::vector<SubMeshPtr>						m_submeshList;

	};
}

