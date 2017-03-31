#include "SimpleDiffuseColorShader.h"

void SimpleDiffuseColorShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadAllToUniform(entity);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(entity->getModel()->getMesh()->getIndices().size()), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleDiffuseColorShader::loadAllToUniform(const std::shared_ptr<Entity> entity)
{	
	loadTransformationToUniform(entity);
	loadToUniform(location_color, entity->getModel()->getMaterial()->getProperties().color);
}

void SimpleDiffuseColorShader::getAllUniformLocations()
{
	std::string temp;

	Shader::getAllUniformLocations();

	temp = "uColor";
	location_color = getUniformLocation(temp);
}
