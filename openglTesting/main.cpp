#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

// GLEW
//#define GLEW_STATIC
//#include <glew.h>

// GLFW
#include <glfw3.h>

#include <stdio.h>
#include <string.h>
#include <cmath> // for the matematical operator absolute

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ToRadians(x) x*(3.14159f/180.0f)



std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;


float rotationAngle;

// Vertex shader
// Must output a clip-space position for that vertex.
// Inputs to a vertex shader are called vertex attributes.
static const char* vShaderLocation = "Shaders/shader.vert";

// fragment shader
static const char* fShaderLocation = "Shaders/shader.frag";

void CreateObjects() {

	//https://paroj.github.io/gltut/Positioning/Tut05%20Optimization%20Base%20Vertex.html
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		1, 2, 3,
		0, 1, 3
	};

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, 1.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
}

void CreateShaders() {

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShaderLocation, fShaderLocation);
	//shader1->CreateFromString(vShader, fShader);
	shaderList.push_back(shader1);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

int main()
{

	Window window(800, 600);
	window.InitWindow();



	CreateObjects();
	CreateShaders();


	glm::mat4 projection = glm::perspective(45.0f,  ((GLfloat)window.GetBufferWidth())/ window.GetBufferHeight(), 0.1f, 100.0f);


	// Loop until window closed
	while (!window.GetShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

	//	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	//	Reshape(bufferWidth, bufferHeight);
		
		rotationAngle += 0.5;
		if (rotationAngle >= 360.0f) {
			rotationAngle = 0;
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					

		shaderList[0]->UseShader();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.f, -2.5f));				
		model = glm::rotate(model, ToRadians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

		glUniformMatrix4fv(shaderList[0]->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(shaderList[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.7f, 0.f, -2.5f));
		model = glm::rotate(model, ToRadians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

		
		glUniformMatrix4fv(shaderList[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

		meshList[1]->RenderMesh();


		glUseProgram(0);

		window.SwapBuffers();
	}

	return 0;
}

