#version 420

const int MAX_LIGHTS = 20;

uniform vec4 matColor;
uniform vec4 matSpecularColor;
uniform float matKa;
uniform float matKd;
uniform float matKs;
uniform float matShininess;
uniform float matToonLevel;

in vec3 surfaceNormal;
in vec4 worldPosition;

out vec4 fragColor;

struct AmbientLight
{
	vec4 color;
	vec4 position;
	float intensity;
	float attenuation;
};

struct PointLight
{
	vec4 position;
	vec4 diffuseColor;
	vec4 specularColor;
	float diffuseIntensity;
	float specularIntensity;
	float attenuation;
};

struct DirectionalLight
{
	vec4 direction;
	vec4 diffuseColor;
	vec4 specularColor;
	float diffuseIntensity;
	float specularIntensity;
};

struct SpotLight
{
	vec4 position;
	vec4 direction;
	vec4 diffuseColor;
	vec4 specularColor;
	float diffuseIntensity;
	float specularIntensity;
	float attenuation;
	float exponent;
	float cutoff;
};

layout(std140, binding = 1) uniform lightSize
{
	uint ambientLightSize;
	uint pointLightSize;
	uint directionalLightSize;
	uint spotLightSize;
};

layout (std140, binding = 2) uniform ambientLightBlock 
{
    AmbientLight ambientLight[MAX_LIGHTS];
};

layout (std140, binding = 3) uniform pointLightBlock
{
	PointLight pointLight[MAX_LIGHTS];
};

layout (std140, binding = 4) uniform toCameraBlock
{
	vec4 cameraPosition;
};

layout (std140, binding = 5) uniform gammaCorrectionBlock
{
	float gammaCorrection;
};

layout (std140, binding = 6) uniform directionalLightBlock
{
	DirectionalLight directionalLight[MAX_LIGHTS];
};

layout (std140, binding = 7) uniform spotLightBlock
{
	SpotLight spotLight[MAX_LIGHTS];
};

vec4 calculateAmbient()
{
	vec4 ambient = vec4(0.0);
	vec3 toLightVector;
	float attenuationFactor;

	for (int i = 0; i < ambientLightSize; ++i)
	{
		toLightVector = ambientLight[i].position.xyz - worldPosition.xyz;
		attenuationFactor = 1.0 / (1.0 + ambientLight[i].attenuation * pow(length(toLightVector), 2));
		ambient += matColor * matKa * ambientLight[i].color * ambientLight[i].intensity * attenuationFactor;
	}
	return ambient;
}

vec4 calculateDiffuse()
{
	vec4 diffuse = vec4(0.0);
	vec3 toLightVector;
	vec3 toLightNormal;
	float attenuationFactor;
	float sDotN;
	float toonFactor;

	for (int i = 0; i < pointLightSize; ++i)
	{
		toLightVector = pointLight[i].position.xyz - worldPosition.xyz;
		toLightNormal = normalize(toLightVector);
		sDotN = max(dot(normalize(surfaceNormal), toLightNormal), 0.0);
		toonFactor = floor ((max(0.0, sDotN)) * matToonLevel);
		attenuationFactor = 1.0 / (1.0 + pointLight[i].attenuation * pow(length(toLightVector), 2));
		diffuse += matColor * matKd * pointLight[i].diffuseColor * pointLight[i].diffuseIntensity  * toonFactor * attenuationFactor ;
	}

	for (int i = 0; i < directionalLightSize; ++i)
	{
		toLightVector = directionalLight[i].direction.xyz;
		toLightNormal = normalize(toLightVector);
		sDotN = max(dot(normalize(surfaceNormal), toLightNormal), 0.0);
		toonFactor = floor ((max(0.0, sDotN)) * matToonLevel);
		diffuse += matColor * matKd * directionalLight[i].diffuseColor * directionalLight[i].diffuseIntensity  * toonFactor;
	}

	for (int i = 0; i < spotLightSize; ++i)
	{
		toLightVector = spotLight[i].position.xyz - worldPosition.xyz;
		toLightNormal = normalize(toLightVector);
		float angle = acos(dot(-toLightNormal, spotLight[i].direction.xyz));
		float cutoff = radians(clamp(spotLight[i].cutoff, 0.0, 90.0)); 
		if( angle < cutoff)
		{
			sDotN = max(dot(surfaceNormal, toLightNormal), 0.0);
			toonFactor = floor ((max(0.0, sDotN)) * matToonLevel);
			float spotFactor = pow(dot(-toLightNormal, spotLight[i].direction.xyz), spotLight[i].exponent);
			attenuationFactor = 1.0 / (1.0 + spotLight[i].attenuation * pow(length(toLightVector), 2));
			diffuse += matColor * matKd * spotLight[i].diffuseColor * spotLight[i].diffuseIntensity  * toonFactor * spotFactor * attenuationFactor;
		}
	}

	return diffuse;
};

vec4 calculateSpecular()
{
	vec4 specular = vec4(0.0);
	vec3 toCamera = normalize((cameraPosition - worldPosition).xyz);
	vec3 toLightVector;
	vec3 toLightNormal;
	float attenuationFactor;
	vec3 reflectedLightDirection;
	float sDotN;
	float toonFactor;

	for (int i = 0; i < pointLightSize; ++i)
	{	
		toLightVector = pointLight[i].position.xyz - worldPosition.xyz;
		toLightNormal = normalize(toLightVector);
		reflectedLightDirection = reflect(-toLightNormal, normalize(surfaceNormal));
		sDotN = max(dot(reflectedLightDirection, toCamera), 0.0);

		if (sDotN > 0.0)
		{
			toonFactor = floor ((max(0.0, sDotN)) * matToonLevel);
			attenuationFactor = 1.0 / (1.0 + pointLight[i].attenuation * pow(length(toLightVector), 2));
			specular += matSpecularColor *  matKs * pointLight[i].specularColor * pointLight[i].specularIntensity * toonFactor * attenuationFactor;
		}
	}

	for (int i = 0; i < directionalLightSize; ++i)
	{	
		toLightVector = directionalLight[i].direction.xyz;
		toLightNormal = normalize(toLightVector);
		reflectedLightDirection = reflect(-toLightNormal, normalize(surfaceNormal));
		sDotN = max(dot(reflectedLightDirection, toCamera), 0.0);
		toonFactor = floor ((max(0.0, sDotN)) * matToonLevel);

		if (sDotN > 0.0)
		{
			specular += matSpecularColor *  matKs * directionalLight[i].specularColor * directionalLight[i].specularIntensity * toonFactor;
		}
	}

	for (int i = 0; i < spotLightSize; ++i)
	{
		toLightVector = spotLight[i].position.xyz - worldPosition.xyz;
		toLightNormal = normalize(toLightVector);
		reflectedLightDirection = reflect(-toLightNormal, normalize(surfaceNormal));
		float angle = acos(dot(-toLightNormal, spotLight[i].direction.xyz));
		float cutoff = radians(clamp(spotLight[i].cutoff, 0.0, 90.0)); 
		if( angle < cutoff)
		{
			sDotN = max(dot(surfaceNormal, toLightNormal), 0.0);
			if (sDotN > 0.0)
			{
				toonFactor = floor ((max(0.0, sDotN)) * matToonLevel);
				float spotFactor = pow(dot(-toLightNormal, spotLight[i].direction.xyz), spotLight[i].exponent);
				attenuationFactor = 1.0 / (1.0 + spotLight[i].attenuation * pow(length(toLightVector), 2));
				specular += matSpecularColor *  matKs * spotLight[i].specularColor * spotLight[i].specularIntensity * toonFactor * attenuationFactor * spotFactor;
			}
		}
	}

	return specular;
}

void main()
{
	vec4 linearColor = calculateAmbient() + calculateDiffuse() + calculateSpecular();
	fragColor = vec4(pow(linearColor.xyz, vec3(gammaCorrection)), linearColor.a);
}