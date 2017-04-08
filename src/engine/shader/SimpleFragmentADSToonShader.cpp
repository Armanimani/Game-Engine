#include "SimpleFragmentADSToonShader.h"

void SimpleFragmentADSToonShader::render(const std::shared_ptr<Entity> entity)
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

void SimpleFragmentADSToonShader::loadAllToUniform(const std::shared_ptr<Entity> entity)
{
	SimpleFragmentADSShader::loadAllToUniform(entity);
	loadToUniform(location_toonLevel, entity->getModel()->getMaterial()->getProperties().toonLevel);
}

void SimpleFragmentADSToonShader::getAllUniformLocations()
{
	std::string temp;

	SimpleFragmentADSShader::getAllUniformLocations();

	temp = "matToonLevel";
	location_toonLevel = getUniformLocation(temp);
}
