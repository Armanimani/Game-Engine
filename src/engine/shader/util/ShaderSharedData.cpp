#include "ShaderSharedData.h"
#include <glm\gtc\type_ptr.inl>

const GLuint MAX_LIGHTS = 20;

void ShaderSharedData::init()
{
	glGenBuffers(1, &matriciesBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, matriciesBuffer);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, matriciesBP, matriciesBuffer, 0, 2 * sizeof(glm::mat4));

	glGenBuffers(1, &lightSizeBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, lightSizeBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightSize), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, lightSizeBP, lightSizeBuffer, 0, sizeof(LightSize));

	glGenBuffers(1, &ambientLightBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, ambientLightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(AmbientLights), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, ambientLightBP, ambientLightBuffer, 0, MAX_LIGHTS * sizeof(AmbientLights));

	glGenBuffers(1, &spotLightBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, spotLightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(SpotLights), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, spotLightBP, spotLightBuffer, 0, MAX_LIGHTS * sizeof(SpotLights));

	glGenBuffers(1, &cameraBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, cameraBP, cameraBuffer, 0, sizeof(glm::vec4));

	glBindBuffer(GL_UNIFORM, 0);
}

void ShaderSharedData::prepare()
{
	projectionMatrix = manager->cameraManager.getActiveCamera()->getProjectionMatrix();
	viewMatrix = manager->cameraManager.getActiveCamera()->getViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, matriciesBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMatrix));

	std::vector<std::shared_ptr<SpotLight>> spotLightList = manager->lightManager.getActiveSpotLights();
	std::vector<std::shared_ptr<AmbientLight>> ambientLightList = manager->lightManager.getActiveAmbientLights();

	LightSize lightSize;
	lightSize.ambientLightSize = min(MAX_LIGHTS, static_cast<GLuint>(ambientLightList.size()));
	lightSize.spotLightSize = min(MAX_LIGHTS, static_cast<GLuint>(spotLightList.size()));
	glBindBuffer(GL_UNIFORM_BUFFER, lightSizeBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightSize), &lightSize);

	AmbientLights ambientLights[MAX_LIGHTS];
	glBindBuffer(GL_UNIFORM_BUFFER, ambientLightBuffer);
	for (std::size_t i = 0; i != lightSize.ambientLightSize; ++i)
	{
		ambientLights[i].color = ambientLightList[i]->getColor();
		ambientLights[i].intensity = ambientLightList[i]->getIntensity();
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, lightSize.ambientLightSize * sizeof(AmbientLights), &ambientLights);

	SpotLights spotLights[MAX_LIGHTS];
	glBindBuffer(GL_UNIFORM_BUFFER, spotLightBuffer);
	for (std::size_t i = 0; i != lightSize.spotLightSize; ++i)
	{
		spotLights[i].position = glm::vec4(spotLightList[i]->getPosition(), 0.0f);
		spotLights[i].diffuseColor = spotLightList[i]->getDiffuseColor();
		spotLights[i].diffuseIntensity = spotLightList[i]->getDiffuseIntensity();
		spotLights[i].specularColor = spotLightList[i]->getSpecularColor();
		spotLights[i].specularIntensity = spotLightList[i]->getSpecularIntensity();
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, lightSize.spotLightSize * sizeof(SpotLight), &spotLights);

	glm::vec4 cameraPosition = glm::vec4(manager->cameraManager.getActiveCamera()->getPosition(), 0.0);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(cameraPosition));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}