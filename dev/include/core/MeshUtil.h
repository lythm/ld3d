#pragma once

namespace ld3d
{
	class EXPORT_CLASS MeshUtil
	{
	public:

		static MeshPtr									CreatePlane(float size, Material2Ptr pMat);
		static MeshPtr									CreateSphere(float radius, float slice, float stack, Material2Ptr pMat);
		static MeshPtr									CreateCube(float size, Material2Ptr pMat);
		static MeshPtr									CreateCone(float range, float angle, float slice, Material2Ptr pMat);
		
		static math::Vector3*							CreateSphere(float radius, float slice, float stack, int& nVerts);
		static math::Vector3*							CreateSpotLightCone(float range, float angle, float slice, int& nVerts);

	private:
		MeshUtil(void);
		virtual ~MeshUtil(void);


	};
}
