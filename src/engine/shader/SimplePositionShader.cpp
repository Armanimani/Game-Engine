#include "SimplePositionShader.h"

SimplePositionShader::SimplePositionShader()
{
	shaderType = ShaderType::SimplePositionShader;
	shaderName = "Simple Position Shader";
	vertexShader = "../src/engine/shader/glsl/SimplePositionVS.glsl";
	fragmentShader = "../src/engine/shader/glsl/SimplePositionFS.glsl";
}

void SimplePositionShader::render(const std::shared_ptr<Mesh> mesh)
{
	start();

	glBindVertexArray(mesh->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}
