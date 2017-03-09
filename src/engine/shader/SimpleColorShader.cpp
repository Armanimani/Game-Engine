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

	loadToUniform(location_transformationMatrix, GLMath::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale()));

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(3);

	glDrawElements(GL_TRIANGLES, entity->getModel()->getMesh()->getIndices().size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);

	stop();
}

void SimpleColorShader::getAllUniformLocations()
{
	std::string temp;
	
	temp = "transformationMatrix";
	location_transformationMatrix = getUniformLocation(temp);
}
