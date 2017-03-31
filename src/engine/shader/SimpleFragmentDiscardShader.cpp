#include "SimpleFragmentDiscardShader.h"

void SimpleFragmentDiscardShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadAllToUniform(entity);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(entity->getModel()->getMesh()->getIndices().size()), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleFragmentDiscardShader::loadAllToUniform(const std::shared_ptr<Entity> entity)
{
	SimpleFragmentADSShader::loadAllToUniform(entity);
	loadToUniform(location_discardScale, entity->getModel()->getMaterial()->getProperties().discardScale);
	loadToUniform(location_discardThickness, entity->getModel()->getMaterial()->getProperties().discardThickness);
}

void SimpleFragmentDiscardShader::getAllUniformLocations()
{
	SimpleFragmentADSShader::getAllUniformLocations();

	std::string temp;

	temp = "matDiscardScale";
	location_discardScale = getUniformLocation(temp);

	temp = "matDiscardThickness";
	location_discardThickness = getUniformLocation(temp);
}
