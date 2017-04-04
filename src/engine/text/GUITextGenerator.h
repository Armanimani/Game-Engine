#pragma once
#include "../model/GUITextModel.h"
#include "Font.h"


class GUITextGenerator
{
public:
	static std::shared_ptr<GUITextModel> createText(const std::string& text, const std::shared_ptr<Font> font, const GLuint& fontSize, const GLfloat& posX, const GLfloat& posY, const GLfloat& maxLength, const std::string& name, const std::shared_ptr<Material> mat);
};