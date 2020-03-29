#version 330 


layout (location=0) in vec3 pos;
layout (location=1) in vec2 tex;
layout (location=2) in vec3 norm;

out vec4 vertexColor;
out vec2 TexCoord;
out vec3 Normal;

//uniform mat4 model;
//uniform mat4 projection;
uniform mat4 cameraToClip;
uniform mat4 modelToWorld;
uniform mat4 worldToCamera;




void main()
{
	gl_Position = cameraToClip * worldToCamera * modelToWorld * vec4(pos, 1.0);
	vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

	TexCoord = tex;

	// for none uniform scaling use the 'transpose(inverse(x))'. 
	// if the scaling is uniform - no need to do this
	Normal = mat3(transpose(inverse(modelToWorld))) * norm;  
}