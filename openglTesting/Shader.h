#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glew.h>
#include <fstream>      // std::ifstream

#include "DirectionalLight.h"
#include "PointLight.h"

#include "CommonValues.h"

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
	void UseShader();
	void SetDirectionalLight(DirectionalLight *directionalLight);

	void SetPointLights(PointLight* pLight, unsigned int lightCount);

	void ClearShader();

	std::string ReadFromFile(const char* fileLocation);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	~Shader();

private:
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

private:
	int PointLightCount;
	GLuint uniformPointLightCount;
	GLuint shaderID, uniformCameraToClip, uniformModelToWorld, uniformWorldToCamera;
	//GLuint uniformAmbientIntensity, uniformAmbientColor;
	//GLuint uniformDirection, uniformDiffuseIntensity;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;

	} UniformDirectionalLight;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint unifromLinear;
		GLuint uniformQuadratic;

	} UniformPointLight[MAX_POINT_LIGTHS];


};

