#include "SimpleDiffuseColorShader.h"

SimpleDiffuseColorShader::SimpleDiffuseColorShader()
{
	shaderType = ShaderType::SimpleDiffuseColorShader;
	shaderName = "Simple Diffuse Color Shader";
	vertexShader = "../src/engine/shader/glsl/SimpleDiffuseColorVS.glsl";
	fragmentShader = "../src/engine/shader/glsl/SimpleDiffuseColorFS.glsl";
}

void SimpleDiffuseColorShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadToUniform(location_color, entity->getModel()->getMaterial()->getProperties().diffuseColor);
	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimpleDiffuseColorShader::getAllUniformLocations()
{
	std::string temp = "uColor";
	location_color = getUniformLocation(temp);
}
