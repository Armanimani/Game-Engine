#include "SimpleColorShader.h"

void SimpleColorShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadAllToUniform(entity);

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(3);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(entity->getModel()->getMesh()->getIndices().size()), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);

	stop();
}

void SimpleColorShader::loadAllToUniform(const std::shared_ptr<Entity> entity)
{
	Shader::loadAllToUniform(entity);
}
