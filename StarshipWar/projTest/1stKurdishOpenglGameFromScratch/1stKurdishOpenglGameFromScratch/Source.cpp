#define STB_IMAGE_IMPLEMENTATION

#include<stdio.h>
#include<string.h>
//#include<stdlib.h>
#include<cmath>
#include<vector> //array list

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<assimp\Importer.hpp>

//#include<glm/mat4x4.hpp> //rotATION TRANSLATION AND SCALE 
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"CommonValues.h" //
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include"SpotLight.h"
#include "PointLight.h"
//#include "SpotLight.h"
#include "Material.h"
#include "MeshGroups.h"


//window dimensions 
//const GLint	WIDTH=800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> MeshList;
std::vector<Shader>shaderList;
////////////Camera stuff
Camera camera;

////////////deltaTime and stuff

//////////////////////////////*****************************************************************************************
Texture brick;
Texture kurd;
Texture fog;

Material shinyMaterial;
Material dullMaterial;

MeshGroups Trump;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];	

GLfloat 	deltaTime = 0.0f;
GLfloat 	lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert.txt";
// Fragment Shader
static const char* fShader = "Shaders/shader.frag.txt";

void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, 
	unsigned int VLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * VLength;
		unsigned int in1 = indices[i+1] * VLength;
		unsigned int in2 = indices[i + 2] * VLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; 	vertices[in0 +1] += normal.y; 	vertices[in0+2] += normal.z;
		vertices[in1] += normal.x; 	vertices[in1 + 1] += normal.y; 	vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; 	vertices[in2 + 1] += normal.y; 	vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / VLength; i++)
	{

		unsigned int nOffset = i * VLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

//void CreateObjects() 
//{
//	unsigned int indices[] = {		
//		0, 3, 1,
//		1, 3, 2,
//		2, 3, 0,
//		0, 1, 2
//	};
//
//	GLfloat vertices[] = {
//	//	x      y      z			u	  v			nx	  ny    nz
//		-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
//		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
//	};
//
//	unsigned int floorIndices[] = {
//		0, 2, 1,
//		1, 2, 3
//	};
//
//	GLfloat floorVertices[] = {
//	-10.0f, -1.0f, -10.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
//	10.0f, -1.0f, -10.0f,	10.0f, 0.0f,	0.0f, 1.0f, 0.0f,
//	-10.0f, -1.5f, 10.0f,	0.0f, 10.0f,	0.0f, 1.0f, 0.0f,
//	10.0f, -0.5f, 10.0f,	10.0f, 10.0f,	0.0f, 1.0f, 0.0f
//	};
//	calcAverageNormals(indices, 12, vertices, 32, 8, 5);
//	//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-Create Object
//	
//	//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-/Create Object
//
//	Mesh *obj1 = new Mesh(); //initialize everything to zero VBO = 0 .... etc 
//	obj1->createMesh(vertices, indices, 32, 12); // 12 vertices for now
//	MeshList.push_back(obj1);
//
//	Mesh *obj2 = new Mesh(); //initialize everything to zero VBO = 0 .... etc 
//	obj2->createMesh(vertices, indices, 32, 12); // 12 vertices for now
//	MeshList.push_back(obj2);
//
//	Mesh *obj3 = new Mesh(); //
//	obj3->createMesh(floorVertices, floorIndices, 32, 6); // 
//	MeshList.push_back(obj3);
//}
void CreateObjects()
{
	const int numVertices = 6000;
	const int numTriangles = 2000;

	// Define the vertices
	GLfloat vertices[numVertices * 8];
	for (int i = 0; i < numVertices; i++) {
		int idx = i * 8;
		vertices[idx] = (rand() % 200 - 100) / 100.0f;  // x
		vertices[idx + 1] = (rand() % 200 - 100) / 100.0f;  // y
		vertices[idx + 2] = (rand() % 200 - 100) / 100.0f;  // z
		vertices[idx + 3] = (float)(i % 10) / 10.0f;  // u
		vertices[idx + 4] = (float)(i / 10) / 10.0f;  // v
		vertices[idx + 5] = 0.0f;  // nx
		vertices[idx + 6] = 1.0f;  // ny
		vertices[idx + 7] = 0.0f;  // nz
	}

	// Define the indices
	unsigned int indices[numTriangles * 3];
	for (int i = 0; i < numTriangles; i++) {
		int idx = i * 3;
		indices[idx] = rand() % numVertices;
		indices[idx + 1] = rand() % numVertices;
		indices[idx + 2] = rand() % numVertices;
	}

	// Calculate average normals
	calcAverageNormals(indices, numTriangles * 3, vertices, numVertices * 8, 8, 5);

	// Create the mesh object and add it to the MeshList
	Mesh* mesh = new Mesh();
	mesh->createMesh(vertices, indices, numVertices * 8, numTriangles * 3);
	MeshList.push_back(mesh);

	Mesh* obj2 = new Mesh(); //initialize everything to zero VBO = 0 .... etc 
		obj2->createMesh(vertices, indices, 32, 12); // 12 vertices for now
		MeshList.push_back(obj2);
	
		
}

void createShaders() {
	Shader *shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1366, 768); //1280 , 1024 or 1024, 768
	mainWindow.initialise();

	//create Triangle
	CreateObjects();
	createShaders();
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f );
	////////////////////////////*****************************************************************************
	fog = Texture("Textures/grass.png"); // Textures/brick.png Textures/kurd.png Textures/kurdi.png Textures/slemani.png Alla
	fog.LoadTexture();
	brick = Texture("Textures/slemani.png"); // Textures/brick.png Textures/kurd.png Textures/kurdi.png Textures/slemani.png Alla
	brick.LoadTexture();
	kurd = Texture("Textures/sand.png"); 
	kurd.LoadTexture(); //kurd = Texture("Textures/kurd.png");   sand.LoadTexture(); 
	                    //kurd.LoadTexture();      sumer.LoadTexture();    grass.LoadTexture();
	                    //0.0f, 1.0f, 1.0f, 0.2f); is green
	shinyMaterial = Material(1.0f, 256); // shininess is going like 2 4 16 32 ...etc
	dullMaterial = Material(0.3f, 4);
	
	Trump = MeshGroups();
	Trump.LoadModel("MeshGroups/x-wing.obj");
	//Trump.LoadModel("MeshGroups/Trump/Trump/insan.obj");
    //Trump.LoadModel("MeshGroups/uh60.obj");


	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,// Matrix Green RGB: 
		                        0.5f, 0.5f,   //ambient , diffuse
								0.0f,0.0f,-1.0f);

	unsigned int pointLightCount = 0;
	//////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& PointLight Stuff
	pointLights[0] = PointLight(0.0f, 3.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	/////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	/////////////////////////////////////***********************************************
	//pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.0f, 1.0f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	//pointLightCount++;
	/////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	/////////////////////////////////////*******************SPOTLIGHT******************
	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f, //rangy Torchaka
								0.0f, 1.0f,
								0.0f, 0.0f, 0.0f, //side
								0.0f,-1.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								20.0f); //how wide is our spread of angle of the SpotLight 'TORCH' is
	spotLightCount++;
////////////////////////////////////////////////////////
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, //side
		-100.0f, -1.0f, 0.0f,//far to left , ....,....
		1.0f, 0.0f, 0.0f,//attenuation , .....,....
		20.0f); //how wide is our spread of angle of the SpotLight 'TORCH' is
	spotLightCount++;
	/////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	/////////////////////////////////////***********************************************
	
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition=0,
		//uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseintensity = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	/*glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		(GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
		*/
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),(GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
		//
		//Assimp::Importer importer = Assimp::Importer();
		//
	//loop untill window closes
	while (!mainWindow.getShouldclose())
	{
		GLfloat now = glfwGetTime(); //IF you using SDL instead of GLFW then ...SDL_getperformancecounter()
		deltaTime = now - lastTime; //for milliSeconds (now - lastTime)* 1000  SDL_getperformanceFrequency()
		lastTime = now;
		//Get + Handle user input ... any event keyboard mouse stuff user moving
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(),deltaTime);
		camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());
		//clear windpw
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//glUseProgram(shader);
		shaderList[0].useShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		//uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		//uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		//uniformDirection = shaderList[0].GetDirectionLocation();
		//uniformDiffuseintensity = shaderList[0].GetDiffuseIntensityLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		spotLights[0].SetFlash(camera.getCameraPosition(), camera.getCameraDirection()); //moving Torch 'Spotlight.cpp, .h

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights,pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour,
			//uniformDiffuseintensity,uniformDirection);

		//glm 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, 
			camera.getCameraPosition().z);
		glm::mat4 model(1.0f);
		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); // order of transforming is important which one comes 1st

		// glUniform1f(uniformXMove,triOffset); //set uniformXmove to the value of triOffset
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		////use Alla**********
		//////////////////////////////////
		brick.useTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity,uniformShininess);
		MeshList[0]->RenderMesh(); //////////mesh 00000000000000000000000000000000000000000
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.1f, 2, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));	//model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		kurd.useTexture(); //dwham dana put it right above MeshList[1]->RenderMesh();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		
		//MeshList[1]->RenderMesh();
		//////////////////////
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));	//////////////////////////////////////
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fog.useTexture(); ////////////////////////////////////////////////
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//MeshList[2]->RenderMesh();
		///////////////////////////////
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004f));	//////////////////////////////////////
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//fog.useTexture(); ////////////////////////////////////////////////
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//MeshList[2]->RenderMesh();
		/////////////////////////////////////
		Trump.RenderModel();

		glUseProgram(0);
		mainWindow.swapbuffers();
		

	}

	return 0;
}
