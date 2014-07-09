#pragma once

#include "packages/atmosphere/SkyDome.h"

namespace ld3d
{
	namespace atmosphere
	{
		class Impl_SkyDome : public SkyDome
		{
		public:

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


			struct Vertex
			{
				math::Vector3									pos;
				math::Color4									clr;
			};
			Impl_SkyDome(GameObjectManagerPtr pManager);
			virtual ~Impl_SkyDome(void);

			bool												OnAttach();
			void												OnDetach();
		private:

			void												CreateIcoSphere(std::vector<math::Vector3>& geo, std::vector<int>& indices, int refine_lvl);

			int													AddVertex(std::vector<math::Vector3>& geo, const math::Vector3& v);
			int													GetMidpoint(std::vector<math::Vector3>& geo, int p1, int p2, std::map<int64, int>& cache);

			Vertex*												CreateSkyDome();

		private:

			GeometryDataPtr										m_pGeometry;
		};
	}
}