#pragma once

namespace ld3d
{
	class _DLL_CLASS MeshUtil
	{
	public:

		static MeshPtr									CreateIcoSphere(float radius, int refine_lvl, MaterialPtr pMat);
		static MeshPtr									CreatePlane(float size, MaterialPtr pMat);
		static MeshPtr									CreateSphere(float radius, float slice, float stack, MaterialPtr pMat);
		static MeshPtr									CreateCube(float size, MaterialPtr pMat);
		static MeshPtr									CreateCone(float range, float angle, float slice, MaterialPtr pMat);
		
		static math::Vector3*							CreateSphere(float radius, float slice, float stack, int& nVerts);
		static math::Vector3*							CreateSpotLightCone(float range, float angle, float slice, int& nVerts);

		static math::Vector3*							CreateCube(float size, int& nVerts);

		static void										CreateUnitIcoSphere(int refine_lvl, std::vector<math::Vector3>& vb, std::vector<int>& ib);

	private:
		struct Triangle
		{
			Triangle(int _v1, int _v2, int _v3)
			{
				v1 = _v1;
				v2 = _v2;
				v3 = _v3;
			}
			int					v1;
			int					v2;
			int					v3;
		};
		static int										IcoSphere_AddVertex(std::vector<math::Vector3>& geo, const math::Vector3& v);
		static int										IcoSphere_GetMidPoint(std::vector<math::Vector3>& geo, int p1, int p2, std::map<int64, int>& cache);

	private:
		MeshUtil(void);
		virtual ~MeshUtil(void);


	};
}
