#pragma once
#include "stdio.h"
#include<GL/glew.h>
#include<GLFW\glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	 
	int initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldclose() {  return glfwWindowShouldClose(mainWindow); }

	bool* getsKeys() { return keys; }
	//reset x y change of mouse to zero 
	GLfloat getXchange(); //la filey window.cpp line 90 ... la videoy 2 bashy Camera 29:19
	GLfloat getYchange();
	void swapbuffers(){ glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat Xchange;
	GLfloat Ychange;
	bool mouseFirstMoved;

	void CreateCallsbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xpos, double ypos);
};

