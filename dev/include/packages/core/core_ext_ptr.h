#pragma once

namespace ld3d
{
	class MeshRenderer;
	class MeshData;
	class WorldMeshRenderer;
	class Behavior;
	class Light_Dir;
	class Light_Point;
	class Light_Spot;
	class Light_Sky;
	class CameraData;
	class OctTreeNode;
	class CameraController_Orbit;

	typedef std::shared_ptr<OctTreeNode>									OctTreeNodePtr;

	typedef std::shared_ptr<CameraController_Orbit>							CameraController_OrbitPtr;
	typedef std::shared_ptr<CameraData>										CameraDataPtr;
	typedef std::shared_ptr<Light_Sky>										Light_SkyPtr;
	typedef std::shared_ptr<Light_Spot>										Light_SpotPtr;
	typedef std::shared_ptr<Light_Point>									Light_PointPtr;
	typedef std::shared_ptr<Light_Dir>										Light_DirPtr;
	typedef std::shared_ptr<Behavior>										BehaviorPtr;
	typedef std::shared_ptr<MeshData>										MeshDataPtr;
	typedef std::shared_ptr<MeshRenderer>									MeshRendererPtr;
	typedef std::shared_ptr<WorldMeshRenderer>								WorldMeshRendererPtr;
}