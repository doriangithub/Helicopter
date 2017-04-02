// Main file of Helicopter game
// Author Dorian Sharevich
// Copyright 2017

#include <QtWidgets\qapplication.h>
#include "MainWidget.h"

int main(int argn, char* argv[])
{
	QApplication app(argn, argv);

	MainWidget mainWidg;
	mainWidg.setGeometry(50, 50, 1200, 600);
	mainWidg.show();
	mainWidg.showMaximized();

	return app.exec();
}