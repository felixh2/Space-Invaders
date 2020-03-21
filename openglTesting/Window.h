#pragma once

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

	~Window();

private:

	GLFWwindow *mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

};

