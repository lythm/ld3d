#pragma once



class GraphicsTest
{
public:
	GraphicsTest(void);
	virtual ~GraphicsTest(void);


	bool										Init(ld3d::CoreApiPtr pCore);
	void										Release();
	void										Update();

private:
	ld3d::CoreApiPtr							m_pCore;
	ld3d::Sys_Graphics2Ptr						m_pGraphics;

};

