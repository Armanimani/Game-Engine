#include "SingnedDistanceOutlineTextShader.h"

void SignedDistanceOutlineTextShader::loadAllToUniform(const std::shared_ptr<GUITextModel> model)
{
	SignedDistanceTextShader::loadAllToUniform(model);

	loadToUniform(location_outlineColor, model->getMaterial()->getProperties().color2);
	loadToUniform(location_outlineWidth, model->getMaterial()->getProperties().fontOutlineWidth);
	loadToUniform(location_outlineEdge, model->getMaterial()->getProperties().fontOutlineEdge);
	loadToUniform(location_outlineOffsetX, model->getMaterial()->getProperties().fontOutlineOffsetX);
	loadToUniform(location_outlineOffsetY, model->getMaterial()->getProperties().fontOutlineOffsetY);
}

void SignedDistanceOutlineTextShader::getAllUniformLocations()
{
	SignedDistanceTextShader::getAllUniformLocations();

	std::string temp;
	
	temp = "matOutlineColor";
	location_outlineColor = getUniformLocation(temp);

	temp = "matOutlineWidth";
	location_outlineWidth = getUniformLocation(temp);

	temp = "matOutlineEdge";
	location_outlineEdge = getUniformLocation(temp);

	temp = "matOutlineOffsetX";
	location_outlineOffsetX = getUniformLocation(temp);

	temp = "matOutlineOffsetY";
	location_outlineOffsetY = getUniformLocation(temp);
}
