#pragma once
#include <QtOpenGL\qgl.h>

class OpenGLWindow : QGLWidget
{
public:
	OpenGLWindow();
	~OpenGLWindow();
protected:
	void initializeGL();
	void loadShapes();
};

