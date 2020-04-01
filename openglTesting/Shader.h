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
	GLuint GetProjectionMatrix();
	GLuint GetModelToWorldLocation();
	GLuint GetWorldToCameraLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();

	// point light
	GLuint GetPointLightDirectionLocation();
	GLuint GetPointLightPositionLocation();
	GLuint GetPointLightQuadraticLocation();
	GLuint GetPointLightLinearLocation();
	GLuint GetPointLightConstLocation();
	GLuint GetPointLightColorLocation();

	void UseShader();
	void ClearShader();

	std::string ReadFromFile(const char* fileLocation);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	~Shader();

private:
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

private:
	GLuint shaderID, uniformCameraToClip, uniformModelToWorld, uniformWorldToCamera;

	// Light
	GLuint uniformAmbientIntensity, uniformAmbientColor;
	GLuint uniformDirection, uniformDiffuseIntensity;

	// Point Light
	GLuint uniformPointLightDirection, uniformPointLightPosition, uniformPointLightColor;
	GLuint uniformPointLightQuadratic, uniformPointLightLinear, uniformPointLightConst;
};

