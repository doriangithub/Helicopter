#pragma once
#include <QtOpenGL\qgl.h>

class OpenGLWindow : public QGLWidget
{
public:
	OpenGLWindow();
	~OpenGLWindow();
protected:
	void initializeGL();
	void loadShapes();
	void setupVertexArrays();
	void installShaders();
	bool checkShaderStatus(GLint shaderID);
	bool checkProgramStatus(GLint programID);
	void paintGL();

	// Title variables
	GLuint numVertTitle;
	GLuint titleVertexBufferID;
	GLuint titleVertex_ARRAY_ObjectID;
	GLuint titleProgramID;
	bool showTitle = true;

	// window variables
	float widthAll;
	float heightAll;

};

