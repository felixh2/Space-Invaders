#version 330 


layout (location=0) in vec3 pos;

out vec4 vertexColor;

//uniform mat4 model;
//uniform mat4 projection;
uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;



void main()
{
	gl_Position = cameraToClipMatrix * modelToCameraMatrix * vec4(pos, 1.0);
	vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}