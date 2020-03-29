#version 330 

out vec4 color; 

in vec2 TexCoord;
in vec4 vertexColor;
in vec3 Normal;

struct DirectionalLight{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	//color=vertexColor;
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)) , 0.0f);
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

	color=texture(theTexture, TexCoord) * (ambientColor + diffuseColor);
}