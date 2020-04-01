#version 330 

out vec4 color; 

in vec4 vertexPosInWorld;
in vec2 TexCoord;
in vec4 vertexColor;
in vec3 Normal;

struct DirectionalLight{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct PointLight{
	vec3 color;
	float quadratic;
	float linear;
	float constant;
	float distance;
	vec3 position;
	vec3 direction;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

void main()
{
	
	//color=vertexColor;
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

	// Directional light
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)) , 0.0f);
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

	// Point light
	vec3 pointLightDirection = vec3(vertexPosInWorld) - pointLight.position;
	float diffuseFactor2 = max(dot(normalize(Normal), normalize(pointLightDirection)) , 0.0f);
	float attenuationFactor = 1/(pointLight.quadratic*pow(length(pointLightDirection),2) + pointLight.linear*length(pointLightDirection) + pointLight.constant);
	float pointLightColor= attenuationFactor*diffuseFactor2;

	color=texture(theTexture, TexCoord) * (ambientColor + pointLightColor );
}