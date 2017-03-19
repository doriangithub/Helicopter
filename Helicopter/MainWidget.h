#pragma once
#include <QtWidgets\qwidget.h>
#include "OpenGLWindow.h"

class MainWidget : public QWidget
{
public:
	OpenGLWindow * GameWindow;

	MainWidget();
	~MainWidget();

protected: 


};

