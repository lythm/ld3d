#pragma once

namespace ld3d
{
	class VoxelWorldMaterialManager
	{
		struct VoxelWorldMaterial
		{
			MaterialPtr											pMaterial;
			TexturePtr											pTex;
		};
	public:
		VoxelWorldMaterialManager(void);
		virtual ~VoxelWorldMaterialManager(void);

		bool													Initialize(RenderManagerPtr pRenderManager);
		void													Release();

		MaterialPtr												GetMaterialByType(uint8 type);

	private:
		std::map<uint8, VoxelWorldMaterial>						m_materials;
	};


}