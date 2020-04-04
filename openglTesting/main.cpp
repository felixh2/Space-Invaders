#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
//#include "Light.h"
#include "DirectionalLight.h"
//#include "Globals.h"
#include "CommonValues.h"
#include "PointLight.h"
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

#include "Camera.h"
#include "Texture.h"

#define ToRadians(x) x*(3.14159f/180.0f)



std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

Texture brickTexture;
Texture dirtTexture;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f; 
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

void calcAverageNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int verticesCount
	, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3) {
		unsigned int in0 = indices[i] * vLength;	// 0
		unsigned int in1 = indices[i+1] * vLength;  // 8
		unsigned int in2 = indices[i+2] * vLength;	// 16

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2); 
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		
		vertices[in0] += normal.x;
		vertices[in0 + 1] = normal.y;
		vertices[in0 + 2] = normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] = normal.y;
		vertices[in1 + 2] = normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] = normal.y;
		vertices[in2 + 2] = normal.z;
	 }

	for (size_t i = 0; i < verticesCount / vLength; i++) {
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; 
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects() {

	//https://paroj.github.io/gltut/Positioning/Tut05%20Optimization%20Base%20Vertex.html
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	// Model-Space Coordinates
	GLfloat vertices[] = {
	//	 x		y		z		 u	  v			 nx	   ny	 nz
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,	    0.5f, 1.0f,		0.0f, 0.0f, 0.0f,
		 0.0f, -0.5f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
								0, 2, 1,
								2, 3, 1
								};

	GLfloat floorVertices[] = {
						//	 x		y		z		
							-10.0f,  0.0f, -10.0f,		0.0f,0.0f,		0.0f, -1.0f, 0.0f,
							 10.0f,	 0.0f, -10.0f,		10.0f,0.0f,		0.0f, -1.0f, 0.0f,
							-10.0f,  0.0f,  10.0f,	    0.0f,10.0f,		0.0f, -1.0f, 0.0f,
							 10.0f,  0.0f,  10.0f,		10.0f,10.f,		0.0f, -1.0f, 0.0f
							};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(floorVertices, floorIndices, 32, 6);
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

	float zOffset = 0;
	
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 90.0f, 5.0f, .1f);
	CreateObjects();
	CreateShaders();

	brickTexture = Texture("Textures/Brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/Dirt.png");
	dirtTexture.LoadTexture();

	DirectionalLight directionalLight(1.0f, 1.0f, 1.0f,
										0.1f, 1.0f,
										1.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;
	PointLight pointLights[MAX_POINT_LIGTHS];
	pointLights[0] = PointLight(
								1.0f, 1.0f, 1.0f,
								0.5f, 1.0f,
								-4.0f, 3.0f, -1.0f,
								0.3f, 0.2f, 0.1f
								);
	pointLightCount++;

	pointLights[1] = PointLight(
								1.0f, 1.0f, 1.0f,
								0.2f, 1.0f,
								4.0f, -1.0f, -1.0f,
								0.3f, 0.2f, 2.1f
								);
	pointLightCount++;

	//pointLights[2] = PointLight(
	//							0.0f, 0.0f, 1.0f,
	//							0.2f, 1.0f,
	//							0.0f, 0.0f, -2.0f,
	//							0.3f, 0.2f, 0.1f
	//							);
	//pointLightCount++;

	glm::mat4 projection = glm::perspective(45.0f,  ((GLfloat)window.GetBufferWidth())/ window.GetBufferHeight(), 0.1f, 100.0f);
	
	
	//PrintMatrix(WorldToCamera);
	// Loop until window closed
	while (!window.GetShouldClose())
	{

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//printf("%0.2f, %0.2f, %0.2f\n", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		camera.KeyControl(window.getKeys(),deltaTime);
		camera.MouseControl(window.getXChange(), window.getYChange());

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

		//glm::mat4 WorldToCamera(1.0f);
		//WorldToCamera = glm::translate(WorldToCamera, glm::vec3(0.0f, 0.0f, zOffset));

		glm::mat4 modelToWorld(1.0f);
		
		
		modelToWorld = glm::translate(modelToWorld, glm::vec3(0.0f, 0.0f, -2.5f));
		modelToWorld = glm::rotate(modelToWorld, ToRadians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		//shaderList[0]->SetDirectionalLight(&directionalLight);
		shaderList[0]->SetPointLights(pointLights, pointLightCount);

		glUniformMatrix4fv(shaderList[0]->GetProjectionMatrix(), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(shaderList[0]->GetModelToWorldLocation(), 1, GL_FALSE, glm::value_ptr(modelToWorld));
		glUniformMatrix4fv(shaderList[0]->GetWorldToCameraLocation(), 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		//--------------------------------------------------------------
		modelToWorld= glm::mat4(1.0f);


		modelToWorld = glm::translate(modelToWorld, glm::vec3(0.0f, -2.0f, 0.0f));
		
		glUniformMatrix4fv(shaderList[0]->GetModelToWorldLocation(), 1, GL_FALSE, glm::value_ptr(modelToWorld));


		brickTexture.UseTexture();
		meshList[1]->RenderMesh();


		glUseProgram(0);

		window.SwapBuffers();
	}

	return 0;
}

