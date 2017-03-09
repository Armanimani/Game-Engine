#include "SimplePositionShader.h"

SimplePositionShader::SimplePositionShader()
{
	shaderType = ShaderType::SimplePositionShader;
	shaderName = "Simple Position Shader";
	vertexShader = "../src/engine/shader/glsl/SimplePositionVS.glsl";
	fragmentShader = "../src/engine/shader/glsl/SimplePositionFS.glsl";
}

void SimplePositionShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadToUniform(location_transformationMatrix, GLMath::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale()));

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	stop();
}

void SimplePositionShader::getAllUniformLocations()
{
	std::string temp;

	temp = "transformationMatrix";
	location_transformationMatrix = getUniformLocation(temp);
}
