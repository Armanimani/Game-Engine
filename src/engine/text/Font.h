#pragma once
#include <string>
#include "FontCharacter.h"
#include <unordered_map>
#include <memory>
#include "../texture/FontTexture.h"

class Font
{
public:
	Font(const std::string& name, const std::string& path) : name(name), path(path)
	{
		path_fnt = path + ".fnt";
		path_png = path + ".png";
	}

	inline void addCharacter(const GLuint& ID, const GLint& x, const GLint& y, const GLint& width, const GLint& height, const GLint& offsetX, const GLint& offsetY, const GLint& advance)
	{
		map.emplace(std::make_pair(ID, std::make_shared<FontCharacter>(ID, x, y, width, height, offsetX + paddingLeft, offsetY + paddingTop, advance)));
		if (ID == 32 ) spaceWidth = map[32]->getAdvance();
	}

	inline void setName(const std::string& value) { name = value; }
	const std::string& getName() { return name; }

	inline void setPath(const std::string& value)
	{
		path = value;
		path_fnt = path + ".fnt";
		path_png = path + ".png";
	}
	inline const std::string& getPath() { return path; }

	inline const std::string& getPath_fnt() { return path_fnt; }
	inline const std::string& getPath_png() { return path_png; }

	inline void setMap(const std::unordered_map<GLuint, std::shared_ptr<FontCharacter>>& value) { map = value; }
	inline const std::unordered_map<GLuint, std::shared_ptr<FontCharacter>>& getMap() { return map; }

	inline const std::shared_ptr<FontCharacter> getCharacter(const GLuint& ID)  {return map[ID]; }
	
	inline void setSize(const GLuint& value) { size = value; }
	inline const GLuint& getSize() { return size; }

	inline void setPaddingTop(const GLuint& value) { paddingTop = value; }
	inline void setPaddingBottom(const GLuint& value) { paddingBottom = value; }
	inline void setPaddingRight(const GLuint& value) { paddingRight = value; }
	inline void setPaddingLeft(const GLuint& value) { paddingLeft = value; }

	inline const GLuint& getPaddingTop() { return paddingTop; }
	inline const GLuint& getPaddingBottom() { return paddingBottom; }
	inline const GLuint& getPaddingRight() { return paddingRight; }
	inline const GLuint& getPaddingLeft() { return paddingLeft; }

	inline void setScaleX(const GLuint& value) { scaleX = value; }
	inline void setScaleY(const GLuint& value) { scaleY = value; }

	inline const GLuint& getScaleX() { return scaleX; }
	inline const GLuint& getScaleY() { return scaleY; }

	inline void setLineHeight(const GLuint& value) { lineHeight = value - paddingBottom - paddingTop; }
	inline const GLuint& getLineHeight() { return lineHeight; }

	inline const GLuint& getSpaceWidth() { return spaceWidth; }

	inline void setTexture (const std::shared_ptr<FontTexture> tex) { texture = tex; }
	inline const std::shared_ptr<Texture> getTexture() { return texture; }

protected:
	std::string name;
	std::string path;
	std::string path_fnt;
	std::string path_png;

	GLuint size;
	GLuint paddingTop;
	GLuint paddingBottom;
	GLuint paddingLeft;
	GLuint paddingRight;

	GLuint scaleX;
	GLuint scaleY;

	GLuint lineHeight;
	GLuint spaceWidth;

	std::shared_ptr<Texture> texture;
	std::unordered_map<GLuint, std::shared_ptr<FontCharacter>> map;
};
