#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>

#include<GL/glew.h>
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"


class Shader
{
public:
	Shader();

	//this reads file and pass to compileShader(); 
	void createFromString(const char* vertexCode, const char* fragmentCode);
	//little bit code in shader here 40:21 vid clearn up code 
	void createFromFiles(const char* vertexLocation, const char* fragmentlocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();
	//we add another function point light lecture 'NOTE: pass it as a pointer * to &mainLight address 
	void SetDirectionalLight(DirectionalLight * dLight);
	void SetPointLights(PointLight * pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight * sLight, unsigned int lightCount);
	void useShader();
	void clearShader();

	~Shader();

private:
	int pointLightCount;
	int spotLightCount;



		GLuint shaderID, uniformProjection, uniformModel,uniformView, uniformEyePosition,
			//uniformAmbientIntensity,uniformAmbientColour,uniformDiffuseIntensity,UniformDirection,
			uniformSpecularIntensity, uniformShininess;
		///Struct
		struct 
		{
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformDirection;
		} uniformDirectionalLight;

		////////End Struct
		GLuint uniformPointLightCount;
		////// another Struct

		struct
		{
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformPosition;
			GLuint uniformConstant;
			GLuint uniformlinear;
			GLuint uniformExponent;
		} uniformPointLight[MAX_POINT_LIGHTS];
		///////
		GLuint uniformSpotLightCount;
		struct 
		{
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformPosition;
			GLuint uniformConstant;
			GLuint uniformlinear;
			GLuint uniformExponent;

			GLuint uniformDirection;
			GLuint uniformedge;

		} uniformSpotLight[MAX_SPOT_LIGHTS];

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

