#include "game_pch.h"
#include "GraphicsTest.h"


GraphicsTest::GraphicsTest(void)
{
}


GraphicsTest::~GraphicsTest(void)
{
}
bool GraphicsTest::Init(ld3d::CoreApiPtr pCore)
{
	m_pCore = pCore;
	m_pGraphics = m_pCore->GetSysGraphics();


	using namespace ld3d;

	Version v1(1, 1, 1, 1);

	Version v2(1, 2, 1, 1);

	bool ret = v1 <= v2; 

	return true;
}
void GraphicsTest::Release()
{
}
void GraphicsTest::Update()
{
}
