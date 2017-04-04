#pragma once
#include <glew\GL\glew.h>

class FontCharacter
{
public:
	FontCharacter(const GLuint& ID, const GLint& x, const GLint& y, const GLint& width, const GLint& height, const GLint& offsetX, const GLint& offsetY, const GLint& advance) : ID(ID), x(x), y(y), width(width), height(height), offsetX(offsetX), offsetY(offsetY), advance(advance) {}

	inline const GLuint& getID() { return ID; }
	inline const GLint& getX() { return x; }
	inline const GLint& getY() { return y; }
	inline const GLint& getWidth() { return width; }
	inline const GLint& getHeight() { return height; }
	inline const GLint& getOffsetX() { return offsetX; }
	inline const GLint& getOffsetY() { return offsetY; }
	inline const GLint& getAdvance() { return advance; }

protected:
	GLuint ID;

	GLint x;
	GLint y;

	GLint width;
	GLint height;

	GLint offsetX;
	GLint offsetY;

	GLint advance;
};