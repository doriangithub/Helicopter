#include <GL\glew.h>
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "OpenGLWindow.h"
#include "ShapeGenerator.h"
#include "ShapeData.h"


////////////////////////////////////////////////////////
//		utility function to read shader file
////////////////////////////////////////////////////////
std::string readShaderCode(const char* fileName)
{
	std::ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "File failed to laod ..." << fileName << std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}


////////////////////////////////////////////////////////
//		function to initialize OpenGL
////////////////////////////////////////////////////////
void OpenGLWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	loadShapes();
	setupVertexArrays();
	installShaders();
	update();
}

////////////////////////////////////////////////////////
//		function to load shapes to draw in OpenGL
////////////////////////////////////////////////////////
void OpenGLWindow::loadShapes()
{
	//
	// set up initial shapes 
	//

	//////////// ENTRY GAME TITLE ///////////
	ShapeData shapeTitle = ShapeGenerator::makeTitle();

	numVertTitle = shapeTitle.numVertices;
	glGenBuffers(1, &titleVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, titleVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shapeTitle.vertexBufferSize(), shapeTitle.vertices, GL_STATIC_DRAW);
	shapeTitle.cleanup();

	/////////////////////////////////////////


}


void OpenGLWindow::setupVertexArrays()
{
	/// ENTRY GAME TITLE
	glGenVertexArrays(1, &titleVertex_ARRAY_ObjectID);
	glBindVertexArray(titleVertex_ARRAY_ObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, titleVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));


}


void OpenGLWindow::installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	std::string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();	// vertexShaderCode;
	glShaderSource(vertexShaderID, 1, adapter, 0);		// 0 - OpenGL, you will figure out the size
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();  // fragmentShadeCode
	glShaderSource(fragmentShaderID, 1, adapter, 0);	// 0 - OpenGL, you will figure out the size

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
	{
		return;
	}

	titleProgramID = glCreateProgram();

	glAttachShader(titleProgramID, vertexShaderID);
	glAttachShader(titleProgramID, fragmentShaderID);

	glLinkProgram(titleProgramID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	if (!checkProgramStatus(titleProgramID))
		return;

	glUseProgram(titleProgramID);
}


bool OpenGLWindow::checkShaderStatus(GLint shaderID)
{
	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
		std::cout << "shader buffer = " << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}


bool OpenGLWindow::checkProgramStatus(GLint programID)
{
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		std::cout << "program buffer = " << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}


void OpenGLWindow::paintGL()
{
	widthAll = width();
	heightAll = height();
	glViewport(0, 0, widthAll, heightAll);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// aspect ratio
	float aspectRatioView = (1.0 / 4.0);

	glm::mat4 scaleMatrixViewState;
	glm::mat4 scaleMatrixView;
	if (aspectRatioView > 1.0)
	{
		scaleMatrixView = glm::scale(glm::mat4(), glm::vec3(1.0f / aspectRatioView, 1.0f, 1.0f));
	}
	else
	{
		scaleMatrixView = glm::scale(glm::mat4(), glm::vec3(1.0f, aspectRatioView, 1.0f));
	}

	//////////////////  SET UP CAMERA ////////////////////

	glm::vec3 eye = glm::vec3(0.0, 0.0f, 0.0f);
	glm::vec3 target = glm::vec3(0.0, 0.0f, -2.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 camera = glm::lookAt(eye, target, up);

	///////////////////////////////////////////////////////


	if (showTitle)
	{	
		glUseProgram(titleProgramID);
		
		// DRAW TITLE
		glBindVertexArray(titleVertex_ARRAY_ObjectID);

		glm::mat4 translationMatrixTitle = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 0.0));
		glm::mat4 rotationMatrixTitle = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 projectionMatrixTitle = glm::ortho(-1, 1, -1, 1, -2, 2);

		//glm::mat4 fullTransfomMatrixTriangl = projectionMatrixTitle * camera * translationMatrixTitle
		//	* scaleMatrixViewState * rotationMatrixTitle;

		glm::mat4 fullTransfomMatrixTriangl = projectionMatrixTitle * translationMatrixTitle
			* scaleMatrixViewState * rotationMatrixTitle;

		GLint fullTransfomMatrixUniformLocationTriangle = glGetUniformLocation(titleProgramID, "fullTransfomMatrix");
		glUniformMatrix4fv(fullTransfomMatrixUniformLocationTriangle, 1, GL_FALSE, &fullTransfomMatrixTriangl[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

}


OpenGLWindow::OpenGLWindow()
{
}


OpenGLWindow::~OpenGLWindow()
{
}
