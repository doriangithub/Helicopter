#if _DEBUG
#include <iostream>
#endif

#include "ShapeGenerator.h"
#include "Vertex.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

ShapeData ShapeGenerator::makeTitle()
{
	ShapeData retShape;

	Vertex triangle[] =
	{
		glm::vec3(0.0f, 1.0f, 0.0f),		// cooordinate
		glm::vec3(1.0f, 0.0f, 0.0f),		// color

		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(+1.0, -1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	retShape.numVertices = NUM_ARRAY_ELEMENTS(triangle);
	retShape.vertices = new Vertex[retShape.numVertices];
	
	memcpy(retShape.vertices, triangle, sizeof(triangle));
	
	GLushort indices[] = { 0, 1, 2 };
	retShape.numIndices = NUM_ARRAY_ELEMENTS(indices);
	retShape.indices = new GLushort[retShape.numIndices];
	
	memcpy(retShape.indices, indices, sizeof(indices));
	
#if _DEBUG 

	std::cout << "--- Shape triangle:" << std::endl;
	std::cout << "numVertices = " << retShape.numVertices << std::endl;
	std::cout << "numIndices = " << retShape.numIndices << std::endl;
	std::cout << "---------------------------" << std::endl;
#endif

	return retShape;
}


