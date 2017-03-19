#include <GL\glew.h>
#include "OpenGLWindow.h"
#include "ShapeGenerator.h"
#include "ShapeData.h"


void OpenGLWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
}

void OpenGLWindow::loadShapes()
{
	//
	// set up initial shapes 
	//

	///// ENTRY GAME TITLE /////
	ShapeData shape = ShapeGenerator::makeTitle();

}

OpenGLWindow::OpenGLWindow()
{
}


OpenGLWindow::~OpenGLWindow()
{
}
