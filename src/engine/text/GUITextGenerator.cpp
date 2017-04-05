#include "GUITextGenerator.h"
#include "TextLine.h"
#include "../Debug/Debug.h"

std::shared_ptr<GUITextModel> GUITextGenerator::createText(const std::string& text, const std::shared_ptr<Font> font, const GLuint& fontSize, const GLfloat& posX, const GLfloat& posY, const GLfloat& length, const GLfloat& lineSpace, const std::string& name, const std::shared_ptr<Material> mat)
{
	GLint viewportWidth = 1;
	GLint viewportHeight = 1;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	viewportWidth = viewport[2];
	viewportHeight = viewport[3];

	GLfloat maxLength = length * viewportWidth * static_cast<GLfloat>(font->getSize()) / static_cast<GLfloat>(fontSize);

	std::vector <std::shared_ptr<TextLine>> data;
	std::shared_ptr<TextLine> line = std::make_shared<TextLine>(font->getSpaceWidth(), maxLength);
	std::shared_ptr<TextWord> word = std::make_shared<TextWord>();
	GLboolean state;
	for (std::size_t i = static_cast<std::size_t> (0); i != text.size(); ++i)
	{
		int ascii = static_cast<int>(text[i]);
		if (ascii == 32)
		{	
			word->addCharacter(font->getCharacter(static_cast<GLuint>(ascii)));
			state = line->addWord(word);
			if (!state)
			{
				data.push_back(line);
				line = std::make_shared<TextLine>(font->getSpaceWidth(), maxLength);
				if (!line->addWord(word))
				{
					Debug::print("unable to create Text");
					Debug::print(text);
					return nullptr;
				}
			}
			word = std::make_shared<TextWord>();
			continue;
		}
		std::shared_ptr<FontCharacter> character = font->getCharacter(static_cast<GLuint>(ascii));
		word->addCharacter(character);
	}
	state = line->addWord(word);
	if (!state)
	{
		data.push_back(line);
		line = std::make_shared<TextLine>(font->getSpaceWidth(), maxLength);
		line->addWord(word);
	}
	data.push_back(line);

	std::shared_ptr<Mesh> mesh;
	std::vector<GLfloat> verts;
	std::vector<GLuint> indices;
	std::vector<MeshAttribute> attribs;
	attribs.push_back(MeshAttribute::position);
	attribs.push_back(MeshAttribute::texture);
	verts.reserve(256);
	verts.reserve(256);

	GLuint currentX = (posX + 1) * viewportWidth * 0.5;
	GLuint currentY = (posY + 1) * viewportHeight * 0.5;

	GLfloat x1;
	GLfloat x2;
	GLfloat x3;
	GLfloat x4;

	GLfloat y1;
	GLfloat y2;
	GLfloat y3;
	GLfloat y4;

	GLuint index = 0;

	GLfloat scale = static_cast<GLfloat>(fontSize) / static_cast<GLfloat>(font->getSize());

	GLfloat scaleTexX = 1.0f / font->getTexture()->getWidth();
	GLfloat scaleTexY = 1.0f / font->getTexture()->getHeight();

	for (std::size_t i = 0; i != data.size(); ++i)
	{
		std::shared_ptr<TextLine> line = data[i];
		std::vector<std::shared_ptr<TextWord>> words = line->getWords();
		for (std::size_t j = 0; j != words.size(); ++j)
		{
			std::shared_ptr<TextWord> word = words[j];
			std::vector<std::shared_ptr<FontCharacter>> characters = word->getCharacters();

			for (std::size_t k = 0; k != characters.size(); ++k)
			{
				std::shared_ptr<FontCharacter> character = characters[k];

				x1 = (currentX + character->getOffsetX() * scale) * 2.0f / viewportWidth - 1.0f;
				x2 = (currentX + character->getOffsetX() * scale + character->getWidth() * scale) * 2.0f / viewportWidth - 1.0f;
				x3 = x2;
				x4 = x1;

				y1 = (currentY - character->getOffsetY() * scale)  * 2.0f / viewportHeight - 1.0f;
				y2 = y1;
				y3 = (currentY - character->getOffsetY() * scale - character->getHeight() * scale) * 2.0f / viewportHeight - 1.0f;
				y4 = y3;

				verts.push_back(x1);
				verts.push_back(y1);
				verts.push_back(0.0f);
				verts.push_back(character->getX() * scaleTexX);
				verts.push_back(character->getY() * scaleTexY);
				verts.push_back(0.0f);

				verts.push_back(x2);
				verts.push_back(y2);
				verts.push_back(0.0f);
				verts.push_back((character->getX() + character->getWidth()) * scaleTexX);
				verts.push_back(character->getY() * scaleTexY);
				verts.push_back(0.0f);

				verts.push_back(x3);
				verts.push_back(y3);
				verts.push_back(0.0f);
				verts.push_back((character->getX() + character->getWidth()) * scaleTexX);
				verts.push_back((character->getY() + character->getHeight()) * scaleTexY);
				verts.push_back(0.0f);

				verts.push_back(x4);
				verts.push_back(y4);
				verts.push_back(0.0f);
				verts.push_back(character->getX() * scaleTexX);
				verts.push_back((character->getY() + character->getHeight()) * scaleTexY);
				verts.push_back(0.0f);

				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 1);
				indices.push_back(index + 2);
				indices.push_back(index + 3);
				index = index + 4;

				currentX += character->getAdvance() * scale;
			}
		}
		currentX = (posX + 1) * viewportWidth * 0.5;
		currentY -= (1.0f + lineSpace) * font->getLineHeight() * scale;
	}
	mesh = std::make_shared<Mesh>("Text", verts, indices, attribs);
	return std::make_shared<GUITextModel>(name, mesh, mat, font);
}
