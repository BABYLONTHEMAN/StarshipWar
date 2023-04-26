#pragma once


#include<GL\glew.h>
#include"stb_image.h"
//#include"Window.h"

class Texture
{
public:

	Texture();

	Texture(const char* fileloc);

	////////////////////////////////

	bool LoadTexture(); // RGB
	bool LoadTextureA(); //RGBA 'A for Alpha'
	//void LoadTexture();
	void useTexture();
	void clearTexture();
	////////////////////////////////
	~Texture();



private:
	GLuint textureID;
	int width, height, bitdepth;
	///////////////
	const char* fileLocation;
};
