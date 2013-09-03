#include "stdafx.h"
#include "gamestudio.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	g_Allocator.Initialize();

	QApplication a(argc, argv);
	QPixmap pic("./assets/standard/texture/15.png");

	QSplashScreen screen(pic);

	screen.show();
	screen.showMessage("loading...", Qt::AlignBottom);
	a.processEvents();
	
	
	GameStudio w;
	w.show();

	screen.finish(&w);

	while(g_app_running)
	{
		a.processEvents();
		w.on_idle();
	//	QThread::msleep(1);
	}

	//g_Allocator.Release();

	return 0;
}
