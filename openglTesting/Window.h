#pragma once
//#include "Globals.h"
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int InitWindow();

	GLint GetBufferWidth() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }

	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void SwapBuffers(){ glfwSwapBuffers(mainWindow); }

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	~Window();


private:

	GLFWwindow *mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	//mouse 
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

};

