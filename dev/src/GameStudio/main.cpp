#include "stdafx.h"
#include "gamestudio.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QPixmap pic("./assets/standard/texture/15.png");

	QSplashScreen screen(pic);

	screen.show();
	screen.showMessage("loading...", Qt::AlignBottom);
	a.processEvents();
	
	
	GameStudio w;
	w.show();

	screen.finish(&w);
	return a.exec();
}
