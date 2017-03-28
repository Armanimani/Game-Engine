#version 420

const int MAX_LIGHTS = 20;

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;

struct AmbientLight
{
	vec4 color;
	float intensity;
};

layout(std140, binding = 0) uniform matricies
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

layout(std140, binding = 1) uniform lightSize
{
	uint ambientLightSize;
	uint spotLightSize;
};

layout (std140, binding = 2) uniform ambientLightBlock 
{
    AmbientLight ambientLight[MAX_LIGHTS];
};

uniform mat4 transformationMatrix;

uniform vec4 matColor;
uniform float matKa;

out vec4 color;
out vec3 surfaceNormal;
out vec4 ambientColor;
out vec4 worldPosition;

vec4 calculateAmbient()
{
	vec4 ambient = vec4(0.0);
	for (int i = 0; i < ambientLightSize; ++i)
	{
		ambient += matColor * matKa * ambientLight[0].color * ambientLight[0].intensity;
	}
	ambient *= matKa;
	return ambient;
}

void main()
{
	worldPosition = transformationMatrix * vec4(vertexPosition, 1.0);
	surfaceNormal = normalize((transformationMatrix * vec4(vertexNormal, 0.0)).xyz);
	color = matColor;
	gl_Position =  projectionMatrix * viewMatrix * worldPosition;;
	ambientColor = calculateAmbient();

}