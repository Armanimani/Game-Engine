#include "SimpleColorShader.h"

SimpleColorShader::SimpleColorShader()
{
	shaderType = ShaderType::SimpleColorShader;
	shaderName = "Simple Color Shader";
	vertexShader = "../src/engine/shader/glsl/SimpleColorVS.glsl";
	fragmentShader = "../src/engine/shader/glsl/SimpleColorFS.glsl";
}

void SimpleColorShader::render(const std::shared_ptr<Mesh> mesh)
{
	start();

	glBindVertexArray(mesh->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(3);

	glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);

}
