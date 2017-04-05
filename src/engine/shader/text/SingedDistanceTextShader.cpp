#include "SingedDistanceTextShader.h"

void SignedDistanceTextShader::render(const std::shared_ptr<GUITextModel> model)
{
	start();

	loadAllToUniform(model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model->getFont()->getTexture()->getID());

	glBindVertexArray(model->getMesh()->getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->getMesh()->getIndices().size()), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE0, 0);
	glActiveTexture(0);

	stop();
}

void SignedDistanceTextShader::loadAllToUniform(const std::shared_ptr<GUITextModel> model)
{
	loadToUniform(location_edge, model->getMaterial()->getProperties().fontEdge);
	loadToUniform(location_width, model->getMaterial()->getProperties().fontWidth);
	loadToUniform(location_color, model->getMaterial()->getProperties().color);
}

void SignedDistanceTextShader::getAllUniformLocations()
{
	std::string temp;

	temp = "matColor";
	location_color = getUniformLocation(temp);

	temp = "matFontEdge";
	location_edge = getUniformLocation(temp);

	temp = "matFontWidth";
	location_width = getUniformLocation(temp);

	temp = "fontTexture";
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
