#pragma once

#include "core/GameObjectComponent.h"

namespace ld3d
{
	class _DLL_CLASS MeshData : public GameObjectComponent
	{
	public:
		MeshData(GameObjectManagerPtr pManager);
		virtual ~MeshData(void);


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
