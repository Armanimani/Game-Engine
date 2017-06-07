#include "SimpleTextureShader.h"

void SimpleTextureShader::render(const std::shared_ptr<Entity> entity)
{
	start();

	loadAllToUniform(entity);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity->getModel()->getMaterial()->getProperties().texture0->getID());

	glBindVertexArray(entity->getModel()->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(entity->getModel()->getMesh()->getIndices().size()), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE0, 0);
	glActiveTexture(0);

	stop();
}

void SimpleTextureShader::loadAllToUniform(const std::shared_ptr<Entity> entity)
{
	loadTransformationToUniform(entity);

	loadToUniform(location_specularColor, entity->getModel()->getMaterial()->getProperties().specularColor);
	loadToUniform(location_Ka, entity->getModel()->getMaterial()->getProperties().ambientReflectivity);
	loadToUniform(location_Kd, entity->getModel()->getMaterial()->getProperties().diffuseReflectivity);
	loadToUniform(location_Ks, entity->getModel()->getMaterial()->getProperties().specularReflectivity);
	loadToUniform(location_shininess, entity->getModel()->getMaterial()->getProperties().shininessFactor);

	prepareTextures();
}

void SimpleTextureShader::getAllUniformLocations()
{
	std::string temp;

	Shader::getAllUniformLocations();

	temp = "matSpecularColor";
	location_specularColor = getUniformLocation(temp);

	temp = "matKa";
	location_Ka = getUniformLocation(temp);

	temp = "matKd";
	location_Kd = getUniformLocation(temp);

	temp = "matKs";
	location_Ks = getUniformLocation(temp);

	temp = "matShininess";
	location_shininess = getUniformLocation(temp);
}

void SimpleTextureShader::prepareTextures()
{
	std::string temp = "matDiffuseTexture";
	GLuint loc = glGetUniformLocation(programID, temp.c_str());
	if (loc >= 0)
	{
		glUniform1i(loc, 0);
	}
	else
	{
		Debug::print("Uniform Variable not found!");
		Debug::print(temp);
		Debug::print(name);
	}
}
