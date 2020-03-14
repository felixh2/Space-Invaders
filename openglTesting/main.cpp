#include <iostream>

// GLEW
#define GLEW_STATIC
#include <glew.h>

// GLFW
#include <glfw3.h>

#include <stdio.h>
#include <string.h>
#include <cmath> // for the matematical operator absolute

// GLM
#include <glm/glm.hpp>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader, uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 1.0f;
float triIncrement = 0.005f;

// Vertex shader
// Must output a clip-space position for that vertex.
// Inputs to a vertex shader are called vertex attributes.
static const char* vShader = "                          \n\
#version 330										    \n\
													    \n\
layout (location=0) in vec3 pos;						\n\
uniform float xMove;									\n\
void main()			 									\n\
{														\n\
	gl_Position = vec4(pos.x + xMove, pos.y, pos.z ,1.0);						\n\
}";

// fragment shader
static const char* fShader = "                          \n\
#version 330										    \n\
													    \n\
out vec4 color;									\n\
void main()												\n\
{														\n\
	color=vec4(0.0,0.0,1.0,1.0);					\n\
}";

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders() {

	shader = glCreateProgram();
	if (!shader) {
		printf("Error creating shader program\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
	}

	uniformXMove = glGetUniformLocation(shader, "xMove");			// demonstration of uniform variable
}

void CreateTriangle() {
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 1.0f, 0.0f,

		 -0.5f, 0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f,
		 0.0f, -1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);		// Create the buffer object stores handle to the object but does not own any memory yet
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // the vertex buffer is bound to the context - GL_ARRAY_BUFFER

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // two operations :
																			   //  1- memory allocation for the buffer bound to the target
																			   //  2- copy data from our memory array into the buffer object
																			   // After this call, the buffer object stores exactly what vertices stores

	glEnableVertexAttribArray(0);											   // The enable call does not have to be called before the vertex attribute
																			   // pointer call, but it does need to be called before rendering.

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);					   // Tell OpenGL how to interpret the array of data stored in the buffer.
																			   // second param - how many of these values(GL_FLOAT) represent a single piece of data
																			   //  glVertexAttribPointer always refers to whatever buffer is bound to GL_ARRAY_BUFFER at the time that this function is called

	glBindBuffer(GL_ARRAY_BUFFER, 0); // By binding the buffer object 0 to GL_ARRAY_BUFFER, we cause the buffer object previously bound to that target to become unbound from it.

	glBindVertexArray(0);
}

void Reshape(int w, int h)
{

	glViewport(0, 0, w, h);
}

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
		Reshape(bufferWidth, bufferHeight);
		
		// Demonstration of the uniform variable 
		 {									
			if (direction) {
				triOffset += triIncrement;
			}
			else {
				triOffset -= triIncrement;
			}

			if (abs(triOffset) >= triMaxOffset) {
				direction = !direction;
			}
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);					// The GL_COLOR_BUFFER_BIT parameter means that the clear call will affect the color buffer

		glUseProgram(shader);							// The shader program to be used by all subsequent rendering commands

		glUniform1f(uniformXMove, triOffset);			// Demonstration of the uniform variable

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);		// Rendering function. It uses the current state to generate a stream of vertices that will form triangles.
												// The second and third parameters represent the start index and the number of indices to read from our vertex data. 

		glBindVertexArray(0);


		glUseProgram(0);


		glfwSwapBuffers(mainWindow);
	}

	return 0;
}

