#pragma once
#include "FontCharacter.h"
#include <vector>
#include <memory>

class TextWord
{
public:
	TextWord(const GLuint& size) : fontSize(size) {}

	inline const GLuint& getWidth() { return width; }
	inline const std::vector<std::shared_ptr<FontCharacter>>& getCharacters() { return chars; }
	inline void addCharacter(const std::shared_ptr<FontCharacter> character)
	{
		chars.push_back(character);
		width += character->getAdvance() * fontSize;
	}

protected:
	std::vector<std::shared_ptr<FontCharacter>> chars;
	GLuint width = 0;
	GLuint fontSize;
};