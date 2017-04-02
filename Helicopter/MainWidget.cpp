#include <QtWidgets\qlayout.h>
#include "MainWidget.h"
#include "OpenGLWindow.h"


MainWidget::MainWidget()
{
	
	QLayout *mainLayout;
	setLayout(mainLayout = new QHBoxLayout);

	gameWindow = new OpenGLWindow();
	mainLayout->addWidget(gameWindow);
	//gameWindow->setMinimumSize(800, 600);
	//gameWindow->setWindowState(Qt::WindowMaximized);
	//gameWindow->showFullScreen();
}

