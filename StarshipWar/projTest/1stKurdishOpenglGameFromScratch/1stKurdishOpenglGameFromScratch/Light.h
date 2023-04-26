#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
		GLfloat aIntensity, GLfloat dIntensity);

	//void UseLight(GLfloat abmbientIntensityLocation, GLfloat ambientColourLocation,
		//GLfloat directionLocation); 
	//these should be GLuint but nvm GLfloat also works anyway
	//but in Material the Teacher uses GLuint

	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity; //is universal lighting 
	//glm::vec3 direction;
	GLfloat diffuseIntensity;
	// diffuse lighting ... is the light coming to a direction and stuff 
};

