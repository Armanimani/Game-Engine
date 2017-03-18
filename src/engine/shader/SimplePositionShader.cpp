#include "SimplePositionShader.h"

void SimplePositionShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadTransformationToUniform(entity);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}
