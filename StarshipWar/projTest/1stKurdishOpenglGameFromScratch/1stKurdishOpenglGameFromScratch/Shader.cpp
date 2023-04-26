#include "Shader.h"
//#include<iostream>
//#include <fstream>
//#include "Texture.h"
Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

	pointLightCount = 0;
	spotLightCount = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)

{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);

}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {


		printf("Failed to read %s| File doesn not exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)

{

	shaderID = glCreateProgram();
	if (!shaderID) {
		printf("error fragment creating ...");

		return;

	}


	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);


	//chunk of code 27:30 

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error Linking Program  %d shader: '%s ", eLog);
		return;

	}
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error Validating Program  %d shader: '%s ", eLog);
		return;

	}
	//uniformModel = glGetUniformLocation(shader, "xMove");
	uniformProjection = glGetUniformLocation(shaderID, "projection"); //idy projection axata naw variably uniformProjection
	uniformModel = glGetUniformLocation(shaderID, "model"); //idy model axata naw variably uniformModel uniformProjection
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction"); //no .base for direction
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");
	
	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)       ///// these are all sets our uniform location values
	{
		char lockBuff[100] = { '\0' };
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].base.colour", i);
		uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformlinear = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
	}
	///////////// SPOT
	uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)       ///// these are all sets our uniform location values
	{
		char lockBuff[100] = { '\0' };
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.base.colour", i);
		uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.position", i);
		uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.constant", i);
		uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.linear", i);
		uniformSpotLight[i].uniformlinear = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].direction", i);
		uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].edge", i);
		uniformSpotLight[i].uniformedge = glGetUniformLocation(shaderID, lockBuff);

	}
}



GLuint Shader::GetProjectionLocation() 
{return uniformProjection;}
GLuint Shader::GetModelLocation()
{
	return uniformModel;
}
GLuint Shader::GetViewLocation()
{
	return uniformView;
}
GLuint Shader::GetAmbientColourLocation()
{
	return uniformDirectionalLight.uniformColour;
}
GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}
GLuint Shader::GetDiffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;

}
GLuint Shader::GetDirectionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}
/////////////////
GLuint Shader::GetSpecularIntensityLocation() {
	return uniformSpecularIntensity;
}
GLuint Shader::GetShininessLocation() {
	return uniformShininess;
}
GLuint Shader::GetEyePositionLocation() {
	return uniformEyePosition;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////
void Shader::SetDirectionalLight(DirectionalLight * dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
		uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}
/////////Point Light <<<<<<<<<<<<<<<
void Shader::SetPointLights(PointLight * pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;
	glUniform1i(uniformPointLightCount,lightCount);
	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour,
			uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
			uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformlinear,
			uniformPointLight[i].uniformExponent);

	}
}
void Shader::SetSpotLights(SpotLight * sLight, unsigned int lightCount)
{
	if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;
	glUniform1i(uniformSpotLightCount, lightCount);
	for (size_t i = 0; i < lightCount; i++)
	{
		sLight[i].UseLight(uniformSpotLight[i].uniformAmbientIntensity, uniformSpotLight[i].uniformColour,
			uniformSpotLight[i].uniformDiffuseIntensity, uniformSpotLight[i].uniformPosition,uniformSpotLight[i].uniformDirection,
			uniformSpotLight[i].uniformConstant, uniformSpotLight[i].uniformlinear,
			uniformSpotLight[i].uniformExponent, uniformSpotLight[i].uniformedge);

	}
}
////////<,,,,,,,,,,,,,,,,,,,,,,,,,,,,


void Shader::useShader()

{
	glUseProgram(shaderID);

}



void Shader::clearShader() {
	if (shaderID != 0) {

		glDeleteProgram(shaderID);
		shaderID = 0;

		}
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)

{

	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);///////////////////////////

	GLint result = 0;
	GLchar eLog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
		{
			glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
			printf("Error compiling %d shader: '%s'\n", shaderType, eLog);
			   return;

	}
	glAttachShader(theProgram, theShader);

}

Shader::~Shader()
{
	clearShader();

}
