#include "Shader.h"



Shader::Shader()
{
	shaderID = 0;
	uniformCameraToClip = 0;
	uniformWorldToCamera = 0;
	uniformModelToWorld = 0; 
	PointLightCount = 0;
}

void Shader::CreateFromString(const char * vertexCode, const char * fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID) {
		printf("Error creating shader program\n");
		return;
	}

	CompileShader(vertexCode, fragmentCode);
}

GLuint Shader::GetProjectionMatrix()
{
	return uniformCameraToClip;
}

GLuint Shader::GetModelToWorldLocation()
{
	return uniformModelToWorld;
}

GLuint Shader::GetWorldToCameraLocation()
{
	return uniformWorldToCamera;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return UniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColorLocation()
{
	return UniformDirectionalLight.uniformColor;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return UniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return UniformDirectionalLight.uniformDirection;
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::SetDirectionalLight(DirectionalLight * directionalLight)
{
	directionalLight->UseDirectionalLight(UniformDirectionalLight.uniformAmbientIntensity, 
											UniformDirectionalLight.uniformColor, 
											UniformDirectionalLight.uniformDiffuseIntensity, 
											UniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight * pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGTHS) {
		lightCount = MAX_POINT_LIGTHS;
	}

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++) {
		pLight[i].UsePointLight(UniformPointLight[i].uniformAmbientIntensity,
								UniformPointLight[i].uniformColor,
								UniformPointLight[i].uniformDiffuseIntensity,
								UniformPointLight[i].uniformPosition,
								UniformPointLight[i].uniformConstant,
								UniformPointLight[i].unifromLinear,
								UniformPointLight[i].uniformQuadratic);
	}

}

void Shader::ClearShader()
{
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;

	}
}

std::string Shader::ReadFromFile(const char * fileLocation)
{
	std::string content;
	std::string line="";
	std::ifstream myfile(fileLocation,std::ios::in);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			std::getline(myfile, line);
			content.append( line + "\n");
		}
		myfile.close();
	}
	else {
		printf("Failed to read file\n");
		return "";
	}
	return content;
}

void Shader::CreateFromFiles(const char * vertexLocation, const char * fragmentLocation)
{
	std::string vertexShader = ReadFromFile(vertexLocation);
	std::string fragmentShader = ReadFromFile(fragmentLocation);

	CreateFromString(vertexShader.c_str(), fragmentShader.c_str());
		
}


Shader::~Shader()
{
	ClearShader();
}

void Shader::CompileShader(const char * vertexCode, const char * fragmentCode)
{

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s\n", eLog);
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s\n", eLog);
	}

	uniformWorldToCamera = glGetUniformLocation(shaderID, "worldToCamera");
	uniformModelToWorld = glGetUniformLocation(shaderID, "modelToWorld");
	uniformCameraToClip = glGetUniformLocation(shaderID, "cameraToClip");
	UniformDirectionalLight.uniformColor = glGetUniformLocation(shaderID, "directionalLight.base.color");
	UniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	UniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	UniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGTHS; i++) {
		char locBuff[100] = { '\0' };
		
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		UniformPointLight[i].uniformColor = glGetUniformLocation(shaderID, locBuff);
		
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		UniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);
		
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		UniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);
		
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		UniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		UniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		UniformPointLight[i].unifromLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].quadratic", i);
		UniformPointLight[i].uniformQuadratic= glGetUniformLocation(shaderID, locBuff);
	}

}

void Shader::AddShader(GLuint theProgram, const char * shaderCode, GLenum shaderType)
{
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
