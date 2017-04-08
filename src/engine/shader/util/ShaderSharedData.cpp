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

	glGenBuffers(1, &pointLightBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, pointLightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(PointLights), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, pointLightBP, pointLightBuffer, 0, MAX_LIGHTS * sizeof(PointLights));

	glGenBuffers(1, &cameraBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, cameraBP, cameraBuffer, 0, sizeof(glm::vec4));

	glGenBuffers(1, &gammaCorrectionBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, gammaCorrectionBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, gammaCorrectionBP, gammaCorrectionBuffer, 0, sizeof(GLfloat));

	glGenBuffers(1, &directionalLightBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, directionalLightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(DirectionalLights), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, directionalLightBP, directionalLightBuffer, 0, MAX_LIGHTS * sizeof(DirectionalLights));

	glGenBuffers(1, &spotLightBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, spotLightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(SpotLights), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, spotLightBp, spotLightBuffer, 0, MAX_LIGHTS * sizeof(SpotLights));

	glGenBuffers(1, &fogBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, fogBuffer);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, fogBp, fogBuffer, 0, 2 * sizeof(glm::vec4));

	glBindBuffer(GL_UNIFORM, 0);
}

void ShaderSharedData::prepare()
{
	projectionMatrix = manager->cameraManager.getActiveCamera()->getProjectionMatrix();
	viewMatrix = manager->cameraManager.getActiveCamera()->getViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, matriciesBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMatrix));


	const std::unordered_map<std::string, std::shared_ptr<Fog>>* fogMap = &(manager->fogManager.getMap());
	glm::vec4 fogColor;
	GLfloat fogDensity;
	for (auto i = fogMap->cbegin(); i != fogMap->cend(); ++i)
	{
		fogColor = (*i).second->getColor();
		fogDensity = (*i).second->getDensity();
		glBindBuffer(GL_UNIFORM_BUFFER, fogBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(fogColor));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), &fogDensity);
	}

	std::vector<std::shared_ptr<PointLight>> pointLightList = manager->lightManager.getActivePointLights();
	std::vector<std::shared_ptr<AmbientLight>> ambientLightList = manager->lightManager.getActiveAmbientLights();
	std::vector<std::shared_ptr<DirectionalLight>> directionalLightList = manager->lightManager.getActiveDirectionalLights();
	std::vector<std::shared_ptr<SpotLight>> spotLightList = manager->lightManager.getActiveSpotLights();

	LightSize lightSize;
	lightSize.ambientLightSize = min(MAX_LIGHTS, static_cast<GLuint>(ambientLightList.size()));
	lightSize.pointLightSize = min(MAX_LIGHTS, static_cast<GLuint>(pointLightList.size()));
	lightSize.directionalLightSize = min(MAX_LIGHTS, static_cast<GLuint>(directionalLightList.size()));
	lightSize.spotLightSize = min(MAX_LIGHTS, static_cast<GLuint>(spotLightList.size()));
	glBindBuffer(GL_UNIFORM_BUFFER, lightSizeBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightSize), &lightSize);

	AmbientLights ambientLights[MAX_LIGHTS];
	glBindBuffer(GL_UNIFORM_BUFFER, ambientLightBuffer);
	for (std::size_t i = 0; i != lightSize.ambientLightSize; ++i)
	{
		ambientLights[i].color = ambientLightList[i]->getColor();
		ambientLights[i].intensity = ambientLightList[i]->getIntensity();
		ambientLights[i].attenuation = ambientLightList[i]->getAttenuationFactor();
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, lightSize.ambientLightSize * sizeof(AmbientLights), &ambientLights);

	PointLights pointLights[MAX_LIGHTS];
	glBindBuffer(GL_UNIFORM_BUFFER, pointLightBuffer);
	for (std::size_t i = 0; i != lightSize.pointLightSize; ++i)
	{
		pointLights[i].position = glm::vec4(pointLightList[i]->getPosition(), 0.0f);
		pointLights[i].diffuseColor = pointLightList[i]->getDiffuseColor();
		pointLights[i].diffuseIntensity = pointLightList[i]->getDiffuseIntensity();
		pointLights[i].specularColor = pointLightList[i]->getSpecularColor();
		pointLights[i].specularIntensity = pointLightList[i]->getSpecularIntensity();
		pointLights[i].attenuation = pointLightList[i]->getAttenuationFactor();
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, lightSize.pointLightSize * sizeof(PointLight), &pointLights);

	glm::vec4 cameraPosition = glm::vec4(manager->cameraManager.getActiveCamera()->getPosition(), 0.0);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(cameraPosition));

	glBindBuffer(GL_UNIFORM_BUFFER, gammaCorrectionBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat), &gammaCorrection);

	DirectionalLights directionalLights[MAX_LIGHTS];
	glBindBuffer(GL_UNIFORM_BUFFER, directionalLightBuffer);
	for (std::size_t i = 0; i != lightSize.directionalLightSize; ++i)
	{
		directionalLights[i].direction = glm::vec4(directionalLightList[i]->getDirection(), 0.0f);
		directionalLights[i].diffuseColor = directionalLightList[i]->getDiffuseColor();
		directionalLights[i].diffuseIntensity = directionalLightList[i]->getDiffuseIntensity();
		directionalLights[i].specularColor = directionalLightList[i]->getSpecularColor();
		directionalLights[i].specularIntensity = directionalLightList[i]->getSpecularIntensity();
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, lightSize.directionalLightSize * sizeof(DirectionalLight), &directionalLights);

	SpotLights spotLights[MAX_LIGHTS];
	glBindBuffer(GL_UNIFORM_BUFFER, spotLightBuffer);
	for (std::size_t i = 0; i != lightSize.spotLightSize; ++i)
	{
		spotLights[i].position = glm::vec4(spotLightList[i]->getPosition(), 0.0f);
		spotLights[i].direction = glm::vec4(spotLightList[i]->getDirection(), 0.0f);
		spotLights[i].diffuseColor = spotLightList[i]->getDiffuseColor();
		spotLights[i].diffuseIntensity = spotLightList[i]->getDiffuseIntensity();
		spotLights[i].specularColor = spotLightList[i]->getSpecularColor();
		spotLights[i].specularIntensity = spotLightList[i]->getSpecularIntensity();
		spotLights[i].attenuation = spotLightList[i]->getAttenuationFactor();
		spotLights[i].exponent = spotLightList[i]->getExponent();
		spotLights[i].cutoff = spotLightList[i]->getCutoff();
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, lightSize.spotLightSize * sizeof(SpotLights), &spotLights);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}