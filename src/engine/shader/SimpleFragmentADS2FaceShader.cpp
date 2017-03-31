#include "SimpleFragmentADS2FaceShader.h"

void SimpleFragmentADS2FaceShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadAllToUniform(entity);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(entity->getModel()->getMesh()->getIndices().size()), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleFragmentADS2FaceShader::loadAllToUniform(const std::shared_ptr<Entity> entity)
{
	loadTransformationToUniform(entity);

	loadToUniform(location_color, entity->getModel()->getMaterial()->getProperties().color);
	loadToUniform(location_specularColor, entity->getModel()->getMaterial()->getProperties().specularColor);
	loadToUniform(location_colorBack, entity->getModel()->getMaterial()->getProperties().colorBack);
	loadToUniform(location_specularColorBack, entity->getModel()->getMaterial()->getProperties().specularColorBack);
	loadToUniform(location_Ka, entity->getModel()->getMaterial()->getProperties().ambientReflectivity);
	loadToUniform(location_Kd, entity->getModel()->getMaterial()->getProperties().diffuseReflectivity);
	loadToUniform(location_Ks, entity->getModel()->getMaterial()->getProperties().specularReflectivity);
	loadToUniform(location_shininess, entity->getModel()->getMaterial()->getProperties().shininessFactor);
}

void SimpleFragmentADS2FaceShader::getAllUniformLocations()
{
	std::string temp;

	Shader::getAllUniformLocations();

	temp = "matColor";
	location_color = getUniformLocation(temp);

	temp = "matSpecularColor";
	location_specularColor = getUniformLocation(temp);

	temp = "matColorBack";
	location_colorBack = getUniformLocation(temp);

	temp = "matSpecularColorBack";
	location_specularColorBack = getUniformLocation(temp);

	temp = "matKa";
	location_Ka = getUniformLocation(temp);

	temp = "matKd";
	location_Kd = getUniformLocation(temp);

	temp = "matKs";
	location_Ks = getUniformLocation(temp);

	temp = "matShininess";
	location_shininess = getUniformLocation(temp);
}
