#include "SimpleDiffuseReflectiveShader.h"
#include <iostream>

void SimpleDiffuseReflectiveShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadTransformationToUniform(entity);
	loadLightsToUniform();

	loadToUniform(location_color, entity->getModel()->getMaterial()->getProperties().diffuseColor);
	loadToUniform(location_Kd, entity->getModel()->getMaterial()->getProperties().diffuseReflectivity);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleDiffuseReflectiveShader::getAllUniformLocations()
{
	std::string temp;

	Shader::getAllUniformLocations();

	temp = "uColor";
	location_color = getUniformLocation(temp);

	temp = "uKd";
	location_Kd = getUniformLocation(temp);

	temp = "uLight_position";
	location_light = getUniformLocation(temp);

	temp = "uLight_intensity";
	location_lightIntensity = getUniformLocation(temp);

	temp = "normalMatrix";
	location_normalMatrix = getUniformLocation(temp);
}

void SimpleDiffuseReflectiveShader::loadTransformationToUniform(const std::shared_ptr<Entity> entity)
{
	Shader::loadTransformationToUniform(entity);
	loadToUniform(location_normalMatrix, glm::transpose(glm::inverse(viewMatrix * GLMath::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale()))));
}

void SimpleDiffuseReflectiveShader::loadLightsToUniform()
{
	loadToUniform(location_light, lights[0]->getPosition());
	loadToUniform(location_lightIntensity, lights[0]->getDiffuseIntensity());
}
