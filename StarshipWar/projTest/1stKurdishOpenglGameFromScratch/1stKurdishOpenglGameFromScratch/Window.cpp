#include "Window.h"



Window::Window()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{

		keys[i] = 0;
	}
	Xchange = 0.0f;
	Ychange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{

	width = windowWidth;
	height = windowHeight;

	//////////////////
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	Xchange = 0.0f;
	Ychange = 0.0f;
	/////////////////////
}



int Window::initialise()
{
	// initialization

		if (!glfwInit())
		{
			printf("GLFW not working initializing ");
			glfwTerminate();
			return 1; //means fails


		}


	//setup GLFW window properties
	//OpemGL Version

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)

	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;

	}

	//int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for GLFW

	glfwMakeContextCurrent(mainWindow);


	//Handle key and mouse input 
	CreateCallsbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//Allow modern extension features
	glewExperimental = GL_TRUE;
	//************	GLenum error = glewInit(); *********//
	//************ if (error! = GLEW_OK) ***************//
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initi... failed ");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();

		return 1;
	}

	//enable depth 
	glEnable(GL_DEPTH_TEST);

	//setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}



//calbacks
void Window::CreateCallsbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

//////////////////////////////////// mouse stuff xchange and stuff
//**********************************************************************//
//&&&&&&&&&&&&&&&&&&&&&& GLfloat getXchange(); 
GLfloat Window::getXchange()
{
	GLfloat theChange = Xchange;
	Xchange = 0.0f;
	return theChange;

}
//&&&&&&&&&&&&&&&&&&&&&&& GLfloat getYchange();

GLfloat Window::getYchange()
{
	GLfloat theChange = Ychange;
	Ychange = 0.0f;
	return theChange;

}
//**********************************************************************//
//////////////////////////////////////////////////////////////////////////


 void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) //staticaka la CPP nanwsit amish har statica xoy
{
	 Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	 //set up mouse control
	 if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	 {
		 glfwSetWindowShouldClose(window, GL_TRUE);
	 }

	 if (key >= 0 && key < 1024)
	 {
		 if (action == GLFW_PRESS)
		 {
			 theWindow->keys[key] = true;

		 }
		 else if (action == GLFW_RELEASE)
		 {

			 theWindow->keys[key] = false;
			 printf("Released : %d\n", key);
		 }
	 }
}
 void Window::handleMouse(GLFWwindow* window, double xpos, double ypos) 
 {
	 Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	 //if very first movement
	 if (theWindow->mouseFirstMoved)
	 {
		 theWindow->lastX = xpos;
		 theWindow->lastY = ypos;
		 theWindow->mouseFirstMoved = false;
	 }
	 theWindow->Xchange = xpos - theWindow->lastX;
	 theWindow->Ychange = theWindow->lastY - ypos;

	 theWindow->lastX = xpos;
	 theWindow->lastY = ypos;

	

 }

Window::~Window()
{
	//if window destroyed terminate glfw 
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
