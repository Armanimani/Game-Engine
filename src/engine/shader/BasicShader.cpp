#include "BasicShader.h"

BasicShader::BasicShader()
{
	shaderType = ShaderType::BasicShader;
	shaderName = "Basic Shader";
	vertexShader = "../src/engine/shader/glsl/BasicVertexShader.glsl";
	fragmentShader = "../src/engine/shader/glsl/BasicFragmentShader.glsl";
}

void BasicShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}
