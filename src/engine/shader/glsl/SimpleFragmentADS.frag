#version 420

const int MAX_LIGHTS = 20;

struct SpotLight
{
	vec4 position;
	vec4 diffuseColor;
	vec4 specularColor;
	float diffuseIntensity;
	float specularIntensity;
};

layout(std140, binding = 1) uniform lightSize
{
	uint ambientLightSize;
	uint spotLightSize;
};


layout (std140, binding = 3) uniform spotLightBlock
{
	SpotLight spotLight[MAX_LIGHTS];
};

layout (std140, binding = 4) uniform toCameraBlock
{
	vec4 cameraPosition;
};

uniform float matKd;
uniform float matKs;
uniform float matShininess;

in vec4 color;
in vec4 ambientColor;
in vec3 surfaceNormal;
in vec4 worldPosition;

out vec4 fragColor;


vec4 calculateDiffuse()
{
	vec4 diffuse = vec4(0.0);
	vec3 toLight;
	float sDotN;
	for (int i = 0; i < spotLightSize; ++i)
	{
		toLight = normalize(spotLight[0].position.xyz - worldPosition.xyz);
		sDotN = max(dot(normalize(surfaceNormal), toLight), 0.0);
		diffuse += color * matKd * spotLight[0].diffuseColor * spotLight[0].diffuseIntensity  * sDotN ;
	}
	return diffuse;
};

vec4 calculateSpecular()
{
	vec4 specular = vec4(0.0);
	vec3 toCamera = normalize((cameraPosition - worldPosition).xyz);
	vec3 toLight;
	vec3 reflectedLightDirection;
	float sDotN;
	for (int i = 0; i < spotLightSize; ++i)
	{	
		toLight = normalize(spotLight[i].position.xyz - worldPosition.xyz);
		reflectedLightDirection = reflect(-toLight, normalize(surfaceNormal));
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
	fragColor = ambientColor + calculateDiffuse() + calculateSpecular();
}