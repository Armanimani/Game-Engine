#include "SimpleVertexADSShader.h"

void SimpleVertexADSShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadTransformationToUniform(entity);
	loadLightsToUniform();

	loadToUniform(location_color, entity->getModel()->getMaterial()->getProperties().diffuseColor);
	loadToUniform(location_Ka, entity->getModel()->getMaterial()->getProperties().ambientReflectivity);
	loadToUniform(location_Kd, entity->getModel()->getMaterial()->getProperties().diffuseReflectivity);
	loadToUniform(location_Ks, entity->getModel()->getMaterial()->getProperties().specularReflectivity);
	loadToUniform(location_shininess, entity->getModel()->getMaterial()->getProperties().shininessFactor);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleVertexADSShader::getAllUniformLocations()
{
	std::string temp;

	Shader::getAllUniformLocations();

	temp = "uColor";
	location_color = getUniformLocation(temp);

	temp = "uKa";
	location_Ka = getUniformLocation(temp);

	temp = "uKd";
	location_Kd = getUniformLocation(temp);

	temp = "uKs";
	location_Ks = getUniformLocation(temp);

	temp = "uShininess";
	location_shininess = getUniformLocation(temp);

	temp = "uLight_position";
	location_lightPosition = getUniformLocation(temp);

	temp = "uLight_ambientIntensity";
	location_lightAmbientIntensity = getUniformLocation(temp);

	temp = "uLight_diffuseIntensity";
	location_lightDiffuseIntensity = getUniformLocation(temp);

	temp = "uLight_specularIntensity";
	location_lightSpecularIntensity = getUniformLocation(temp);

	temp = "normalMatrix";
	location_normalMatrix = getUniformLocation(temp);
}

void SimpleVertexADSShader::loadTransformationToUniform(const std::shared_ptr<Entity> entity)
{
	Shader::loadTransformationToUniform(entity);
	loadToUniform(location_normalMatrix, glm::transpose(glm::inverse(viewMatrix * GLMath::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale()))));
}

void SimpleVertexADSShader::loadLightsToUniform()
{
	loadToUniform(location_lightPosition, lights[0]->getPosition());
	loadToUniform(location_lightDiffuseIntensity, lights[0]->getDiffuseIntensity());
	loadToUniform(location_lightSpecularIntensity, lights[0]->getSpecularIntensity());
}