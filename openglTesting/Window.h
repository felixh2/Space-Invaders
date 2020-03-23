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
	float getUp();

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	~Window();


private:

	GLFWwindow *mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[10];
	float up;
};

