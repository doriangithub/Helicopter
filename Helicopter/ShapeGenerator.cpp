#include "ShapeGenerator.h"
#include "Vertex.h"

ShapeData ShapeGenerator::makeTitle()
{
	ShapeData retShape;

	Vertex thisTri[] =
	{
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(+1.0, -1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	//retShape.numVertices = NUM_ARRAY_ELEMENTS(thisTri);
	//retShape.vertices = new Vertex[retShape.numVertices];
	//
	//memcpy(retShape.vertices, thisTri, sizeof(thisTri));
	//
	//GLushort indices[] = { 0, 1, 2 };
	//retShape.numIndices = NUM_ARRAY_ELEMENTS(indices);
	//retShape.indices = new GLushort[retShape.numIndices];
	//
	//memcpy(retShape.indices, indices, sizeof(indices));
	//
	return retShape;
}

ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}
