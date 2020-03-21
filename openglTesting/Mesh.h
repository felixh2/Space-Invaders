#pragma once
// GLEW
#define GLEW_STATIC
#include <glew.h>

class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount; 
};

