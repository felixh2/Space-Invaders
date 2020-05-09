#pragma once
#include<glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);
	bool LoadTexture();
	bool LoadTextureA(); // Texture with Alpha channel
	void UseTexture();
	void ClearTexture();
	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;
	const char* fileLocation;
};

