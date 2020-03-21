#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glew.h>
#include <fstream>      // std::ifstream

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	void UseShader();
	void ClearShader();

	std::string ReadFromFile(const char* fileLocation);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	~Shader();

private:
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

private:
	GLuint shaderID, uniformProjection, uniformModel;
};

