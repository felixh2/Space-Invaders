#version 330 


layout (location=0) in vec3 pos;

out vec4 vertexColor;

//uniform mat4 model;
//uniform mat4 projection;
uniform mat4 cameraToClip;
uniform mat4 modelToWorld;
uniform mat4 worldToCamera;



void main()
{
	gl_Position = cameraToClip * worldToCamera * modelToWorld * vec4(pos, 1.0);
	vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}