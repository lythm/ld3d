#pragma once

namespace ld3d
{
	class VoxelPolygonizer
	{
	public:
		
		struct Face
		{
			math::Vector3	v[3];
		};

		VoxelPolygonizer(void);
		virtual ~VoxelPolygonizer(void);


		void													Reset();

		void													Process(VoxelWorldPtr pWorld);

		const std::vector<Face>&								GetFaces();

	private:
		std::vector<Face>										m_faces;

	};
}
