#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = "";
	stbi_set_flip_vertically_on_load(true);

}

Texture::Texture(const char* fileloc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = fileloc;
}
///////////////////////////

////////////////////////////////// TEXTURE 
bool Texture::LoadTexture()
{
	unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitdepth, 0);
	if (!texData)
	{
		printf(" failed ...to do stuff find: %s\n", fileLocation);
		return false;
	}
	////// gl stuff
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);
	///////////////////////////// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	//stbi_image_free(texData);
	return true;
}

//////////////////////////////////// TEXTURE A
bool Texture::LoadTextureA()
{
	unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitdepth, 0);
	if (!texData)
	{
		printf(" failed ...to do stuff find: %s\n", fileLocation);
		return false;
	}
	////// gl stuff
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);
	///////////////////////////// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	//stbi_image_free(texData);
	return true;
}
/////////// ENDOF TEXTURE A
//*******************************************************************


//////////// Last class we make 18:57 
void Texture::useTexture()
{
	//texture unit and stuff 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

}

////////////

void Texture::clearTexture()
{

	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = "";

}



//free up the memory 
Texture::~Texture()
{
	clearTexture();
}
