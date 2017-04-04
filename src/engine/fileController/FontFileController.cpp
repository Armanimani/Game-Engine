#include "FontFileController.h"
#include<fstream>
#include "FileController.h"
#include <sstream>
#include <algorithm>
#include "../texture/FontTexture.h"

const std::string FONTSIZE = "size";
const std::string PADDING = "padding";
const std::string SCALEW = "scaleW";
const std::string SCALEH = "scaleH";
const std::string LINE_HEIGHT = "lineHeight";

std::shared_ptr<Font> FontFileController::readFile(const std::string & inputPath)
{
	std::string path = inputPath;
	std::string path_fnt = path + ".fnt";
	std::string name = std::string(path.begin() + path.find_last_of("/") + 1, path.end());
	std::shared_ptr<Font> font = std::make_shared<Font>(name, path);

	std::ifstream file;
	FileController::openFile(file, path_fnt);

	std::string line;
	std::string key;
	std::string stringTemp;

	bool state = false;

	GLint temp[8];
	while (std::getline(file, line))
	{
		std::istringstream lineStream(line);
		lineStream >> key;
		if (key == "info")
		{
			auto pos = line.find(FONTSIZE);
			font->setSize(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 5, line.begin() + pos + 5 + 3))));

			pos = line.find(PADDING);
			font->setPaddingTop( static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 8, line.begin() + pos + 9))));
			font->setPaddingLeft(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 10, line.begin() + pos + 11))));
			font->setPaddingBottom(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 12, line.begin() + pos + 13))));
			font->setPaddingRight(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 14, line.begin() + pos + 15))));
		}

		if (key == "common")
		{
			auto pos = line.find(LINE_HEIGHT);
			font->setLineHeight(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 11, line.begin() + pos + 14))));

			pos = line.find(SCALEW);
			font->setScaleX(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 7, line.begin() + pos + 11))));
			pos = line.find(SCALEH);
			font->setScaleY(static_cast<GLuint> (std::stoi(std::string(line.begin() + pos + 7, line.begin() + pos + 11))));
		}

		if (key == "char")
		{
			for (std::size_t i = 0; i != 8; ++i)
			{
				lineStream >> stringTemp;
				temp[i] = static_cast<GLint>(std::stoi(std::string(stringTemp.begin() + stringTemp.find_last_of("=") + 1, stringTemp.end())));
			}
			font->addCharacter(static_cast<GLuint>(temp[0]), temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);
		}
	}

	std::shared_ptr<FontTexture> texture = std::make_shared<FontTexture>(font->getName(), font->getPath_png(), font->getScaleX(), font->getScaleY());
	font->setTexture(texture);

	return font;
}
