#pragma once

#include<GL/glew.h>
class Mesh
{
public:
	Mesh();

	void createMesh(const GLfloat* vertices, const unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void clearMesh();

	~Mesh();


private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	GLenum error;
};

