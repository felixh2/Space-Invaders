#version 330 

out vec4 color; 

in vec2 TexCoord;
in vec4 vertexColor;
in vec3 Normal;
in vec3 FragPos;

const int MAX_POINT_LIGHTS = 3;

struct Light{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct PointLight{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight{
	Light base;
	vec3 direction;

};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;


vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)) , 0.0f);
	vec4 diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

	return  (ambientColor + diffuseColor);
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalcPointLights()
{
	vec4 totalColor = vec4(0.0f, 0.0f, 0.0f, 0.0f); 

	for(int i=0 ; i < pointLightCount ; i++){
		vec3 direction = FragPos - pointLights[i].position;
		float distance = length(direction);
		vec4 color =  CalcLightByDirection(pointLights[i].base, normalize(direction));
		float attenuation = 1/(pointLights[i].quadratic * pow(distance,2) + pointLights[i].linear*distance + pointLights[i].constant);
		totalColor += (color * attenuation);
	}
	return totalColor;
}

void main()
{
	vec4 finalColor = CalcDirectionalLight() + CalcPointLights();
	color=texture(theTexture, TexCoord) * finalColor;
}