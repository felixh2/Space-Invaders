#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
//#include "Globals.h"

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
extern float goForward = 0;

// Vertex shader
// Must output a clip-space position for that vertex.
// Inputs to a vertex shader are called vertex attributes.
static const char* vShaderLocation = "Shaders/shader.vert";

// fragment shader
static const char* fShaderLocation = "Shaders/shader.frag";

void PrintMatrix(glm::mat4 theMat) {
	
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf(" %f ", theMat[i][j]);
		}
		printf("\n");
	}
}

void CreateObjects() {

	//https://paroj.github.io/gltut/Positioning/Tut05%20Optimization%20Base%20Vertex.html
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		1, 2, 3,
		0, 1, 3
	};

	// Model-Space Coordinates
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, 1.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	/*Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);*/
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

	float zOffset = 0;
	

	CreateObjects();
	CreateShaders();


	glm::mat4 projection = glm::perspective(45.0f,  ((GLfloat)window.GetBufferWidth())/ window.GetBufferHeight(), 0.1f, 100.0f);
	
	
	//PrintMatrix(WorldToCamera);
	// Loop until window closed
	while (!window.GetShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		rotationAngle += 0.5;
		if (rotationAngle >= 360.0f) {
			rotationAngle = 0;
		}

		zOffset += 0.1;
		

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					

		shaderList[0]->UseShader();

		glm::mat4 WorldToCamera(1.0f);
		WorldToCamera = glm::translate(WorldToCamera, glm::vec3(0.0f, 0.0f, zOffset));

		glm::mat4 modelToWorld(1.0f);
		
		
		modelToWorld = glm::translate(modelToWorld, glm::vec3(0.0f, 0.0f, -100.0f));
		modelToWorld = glm::rotate(modelToWorld, ToRadians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));


		glUniformMatrix4fv(shaderList[0]->GetProjectionMatrix(), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(shaderList[0]->GetModelToWorldLocation(), 1, GL_FALSE, glm::value_ptr(modelToWorld));
		glUniformMatrix4fv(shaderList[0]->GetWorldToCameraLocation(), 1, GL_FALSE, glm::value_ptr(WorldToCamera));

		meshList[0]->RenderMesh();


		glUseProgram(0);

		window.SwapBuffers();
	}

	return 0;
}

