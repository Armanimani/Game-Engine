#pragma once

#include "Shape.h"

class RectangleShape : public Shape
{
public:
	RectangleShape(const GLuint& xMin, const GLuint& xMax, const GLuint& yMin, const GLuint yMax) : Shape(ShapeType::rectangle), xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}

	inline void setXMin(const GLuint& value) { xMin = value; }
	inline void setXMax(const GLuint& value) { xMax = value; }
	inline void setYMin(const GLuint& value) { yMin = value; }
	inline void setYMax(const GLuint& value) { yMax = value; }

	inline const GLuint& getXMin() { return xMin; }
	inline const GLuint& getXMax() { return xMax; }
	inline const GLuint& getYMin() { return yMin; }
	inline const GLuint& getYMax() { return yMax; }

	inline const GLuint getWidth() { return xMax - xMin; }
	inline const GLuint getHeight() { return yMax - yMin; }
	inline const GLfloat getAspectRatio() { return static_cast<GLfloat>(getWidth()) / static_cast<GLfloat>(getHeight()); }

	virtual inline const GLboolean isInside(const GLuint& x, const GLuint& y)
	{
		return (x >= xMin && x <= xMax && y >= yMin && y <= yMax) ? true : false;
	}
	virtual inline const GLboolean isInside(const FVec2& value) { return isInside(value.x, value.y); }
	virtual inline const GLboolean isInside(const USIVec2& value) { return isInside(value.x, value.y); }

protected:
	GLuint xMin;
	GLuint xMax;
	GLuint yMin;
	GLuint yMax;

};