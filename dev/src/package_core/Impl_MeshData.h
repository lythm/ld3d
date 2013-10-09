#pragma once

#include "packages/core/MeshData.h"

namespace ld3d
{
	class Impl_MeshData : public MeshData
	{
	public:
		Impl_MeshData(GameObjectManagerPtr pManager);
		virtual ~Impl_MeshData(void);


		void						Update(float dt);
		MeshPtr						GetMesh();
		void						SetMesh(MeshPtr pMesh);
		bool						OnAttach();
		void						OnDetach();

		bool						SetMeshAsset(const std::string& asset);
		const std::string&			GetMeshAsset();


		bool						OnSerialize(DataStream* pStream);
		bool						OnUnSerialize(DataStream* pStream, const Version& version );


	private:
		bool						LoadMesh(const std::string& asset);
		void						ResetMeshRenderer();
	private:
		MeshPtr						m_pMesh;

		std::string				m_meshAsset;
	};
}
