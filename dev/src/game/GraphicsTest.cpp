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
	using namespace ld3d;

	m_pCore = pCore;
	m_pGraphics = m_pCore->GetSysGraphics();

	
	return true;
}
void GraphicsTest::Release()
{
}
void GraphicsTest::Update()
{
}
