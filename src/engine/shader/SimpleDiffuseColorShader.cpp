#include "SimpleDiffuseColorShader.h"

void SimpleDiffuseColorShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadTransformationToUniform(entity);

	loadToUniform(location_color, entity->getModel()->getMaterial()->getProperties().color);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleDiffuseColorShader::getAllUniformLocations()
{
	std::string temp;

	Shader::getAllUniformLocations();

	temp = "uColor";
	location_color = getUniformLocation(temp);
}
