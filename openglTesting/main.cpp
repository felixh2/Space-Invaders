#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <iostream>
#include <vector>
//#include "Globals.h"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Light.h"
#include "Camera.h"
#include "Texture.h"
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

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
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
	
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 90.0f, 5.0f, .1f);
	CreateObjects();
	CreateShaders();

	brickTexture = Texture("Textures/Brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/Dirt.png");
	dirtTexture.LoadTexture();

	Light mainLight(1.0f, 1.0f, 1.0f, 0.1f, 2.0f, 0.0f, 0.0f, 1.0f);
	PointLight pointLight(1.0f, 1.0f, 1.0f, 1.0f, 0.045f, 0.0075f, glm::vec3(2.0f, 0.0f,-2.0f));

	
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
		
		
		modelToWorld = glm::translate(modelToWorld, glm::vec3(0.0f, 0.0f, -2.0f));
		//modelToWorld = glm::rotate(modelToWorld, ToRadians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));


		glUniformMatrix4fv(shaderList[0]->GetProjectionMatrix(), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(shaderList[0]->GetModelToWorldLocation(), 1, GL_FALSE, glm::value_ptr(modelToWorld));
		glUniformMatrix4fv(shaderList[0]->GetWorldToCameraLocation(), 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		
		brickTexture.UseTexture();

		mainLight.UseLight( shaderList[0]->GetAmbientIntensityLocation(),
						    shaderList[0]->GetAmbientColorLocation(),
							shaderList[0]->GetDiffuseIntensityLocation(),
							shaderList[0]->GetDirectionLocation()
		);
		pointLight.UsePointLight(shaderList[0]->GetPointLightQuadraticLocation(),
								 shaderList[0]->GetPointLightLinearLocation(),
								 shaderList[0]->GetPointLightConstLocation(),
								 shaderList[0]->GetPointLightPositionLocation(),
							     shaderList[0]->GetPointLightColorLocation()
		);

		meshList[0]->RenderMesh();


		glUseProgram(0);

		window.SwapBuffers();
	}

	return 0;
}

