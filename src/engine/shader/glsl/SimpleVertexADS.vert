#version 420

const int MAX_LIGHTS = 20;

struct AmbientLight
{
	vec4 color;
	float intensity;
};

struct SpotLight
{
	vec4 position;
	vec4 diffuseColor;
	vec4 specularColor;
	float diffuseIntensity;
	float specularIntensity;
};

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;

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

layout (std140, binding = 3) uniform spotLightBlock
{
	SpotLight spotLight[MAX_LIGHTS];
};

layout (std140, binding = 4) uniform toCameraBlock
{
	vec4 cameraPosition;
};

uniform mat4 transformationMatrix;
//uniform mat4 normalMatrix;

uniform vec4 matColor;
uniform float matKd;
uniform float matKa;
uniform float matKs;
uniform float matShininess;

out vec4 color;

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

vec4 calculateDiffuse(vec3 surfaceNormal, vec4 worldPosition)
{
	vec4 diffuse = vec4(0.0);
	vec3 toLight;
	float sDotN;
	for (int i = 0; i < spotLightSize; ++i)
	{
		toLight = normalize(spotLight[i].position.xyz - worldPosition.xyz);
		sDotN = max(dot(surfaceNormal, toLight), 0.0);
		diffuse += matColor * matKd * spotLight[i].diffuseColor * spotLight[i].diffuseIntensity  * sDotN ;
	}
	return diffuse;
};

vec4 calculateSpecular(vec3 surfaceNormal, vec4 worldPosition)
{
	vec4 specular = vec4(0.0);
	vec3 toCamera = normalize((cameraPosition - worldPosition).xyz);
	vec3 toLight;
	vec3 reflectedLightDirection;
	float sDotN;
	for (int i = 0; i < spotLightSize; ++i)
	{	
		toLight = normalize(spotLight[i].position.xyz - worldPosition.xyz);
		reflectedLightDirection = reflect(-toLight, surfaceNormal);
		sDotN = max(dot(reflectedLightDirection, toCamera), 0.0);
		if (sDotN > 0.0)
		{
			specular += matKs * spotLight[i].specularColor * spotLight[i].specularIntensity * pow(sDotN, 50.0);
		}
	}
	return specular;
}

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(vertexPosition, 1.0);
	vec4 position = projectionMatrix * viewMatrix * worldPosition;
	vec3 surfaceNormal = normalize((transformationMatrix * vec4(vertexNormal, 0.0)).xyz);
	color = calculateAmbient() + calculateDiffuse(surfaceNormal , worldPosition) + calculateSpecular(surfaceNormal , worldPosition);
	gl_Position = position;

}