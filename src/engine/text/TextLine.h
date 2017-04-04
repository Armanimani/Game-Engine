#pragma once

#include "TextWord.h"

class TextLine
{
public:
	TextLine(const GLuint& spaceWidth, const GLuint& maxLength) : spaceWidth(spaceWidth), maxLength(maxLength) {}

	inline GLboolean addWord(const std::shared_ptr<TextWord>& word)
	{
		GLuint addedLength = word->getWidth();
		addedLength += (words.empty()) ? 0 : spaceWidth;
		if (length + addedLength <= maxLength)
		{
			words.push_back(word);
			length += addedLength;
			return true;
		}
		return false;
	}

	inline const std::vector<std::shared_ptr<TextWord>> getWords() { return words; }
	inline const GLuint& getLength() { return length; }
	inline const GLuint& getMaxLength() { return maxLength; }
protected:
	std::vector<std::shared_ptr<TextWord>> words;
	GLuint spaceWidth;
	GLuint maxLength;
	GLuint length = 0;
};