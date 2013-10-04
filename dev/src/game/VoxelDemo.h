#pragma once
class VoxelDemo
{
public:
	VoxelDemo();
	virtual ~VoxelDemo(void);

	bool										Init(ld3d::CoreApiPtr pCore);
	void										Release();
	void										Update();


	void										_on_key_state(ld3d::EventPtr pEvent);

private:
	ld3d::CoreApiPtr							m_pCore;
	ld3d::CameraPtr								m_pCamera;

	ld3d::GameObjectPtr							m_pWorld;
};

