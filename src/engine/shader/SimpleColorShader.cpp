#include "SimpleColorShader.h"

SimpleColorShader::SimpleColorShader()
{
	shaderType = ShaderType::SimpleColorShader;
	shaderName = "Simple Color Shader";
	vertexShader = "../src/engine/shader/glsl/SimpleColorVS.glsl";
	fragmentShader = "../src/engine/shader/glsl/SimpleColorFS.glsl";
}

void SimpleColorShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(3);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);

}
