#include "Mesh.h"
#include <iostream>
//#include "Window.h"
//#include "Texture.h"

Mesh::Mesh()
{
	VAO =0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

}


	// Create mesh using given vertex and index data
	void Mesh::createMesh(const GLfloat * vertices, const unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) {
		// Save the number of indices for rendering later
		indexCount = numOfIndices;

		// Generate and bind vertex array object (VAO)
		glGenVertexArrays(1, &VAO); 
		glBindVertexArray(VAO); 

		// Generate and bind index buffer object (IBO)
		glGenBuffers(1, &IBO); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numOfIndices, indices, GL_STATIC_DRAW); 

		// Generate and bind vertex buffer object (VBO)
		glGenBuffers(1, &VBO); 
		glBindBuffer(GL_ARRAY_BUFFER, VBO); 
		/*glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numOfVertices * 8, vertices, GL_STATIC_DRAW); */
		if (vertices != nullptr) { 
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW); 
		}
		else {
			// handle null pointer case
			// for example, print an error message and return
			std::cerr << "Error: vertices pointer is null" << std::endl; 
			return; 
		}
		// Set vertex attribute pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0); 
		glEnableVertexAttribArray(0); 
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3)); 
		glEnableVertexAttribArray(1); 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5)); 
	glEnableVertexAttribArray(2); 

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//UNBIND
	
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << error << std::endl;
	}
}



void Mesh::RenderMesh()   //called glDrawElements 
{
	glBindVertexArray(VAO);// bakary aheninawa Bindy akain hamw jare ka bakary ahenin
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //some times doesn't need to bind this IBO, this for some graphic card buggs
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);// wena akeshin 
	//When glDrawElements is called,it uses count sequential elements from an enabled array, starting at indices to construct a sequence of geometric primitives.
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind IBO ka eshman penama
	glBindVertexArray(0); //unbind VAO ka eshman penama 

}


void Mesh::clearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;

	}
	indexCount = 0;
}


Mesh::~Mesh()
{

	clearMesh();
}
