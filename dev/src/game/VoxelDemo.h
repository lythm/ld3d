#pragma once
class VoxelDemo
{
public:
	VoxelDemo();
	virtual ~VoxelDemo(void);

	bool										Init(ld3d::CoreApiPtr pCore);
	void										Release();
	void										Update();

	void										_on_mouse_move(ld3d::EventPtr pEvent);
	void										_on_mouse_wheel(ld3d::EventPtr pEvent);
	void										_on_mouse_button(ld3d::EventPtr pEvent);
	
private:
	ld3d::CoreApiPtr							m_pCore;
	ld3d::CameraPtr								m_pCamera;

};

