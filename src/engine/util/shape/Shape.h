#pragma once

#include <glew\GL\glew.h>
#include "ShapeType.h"
#include "../vector/FVec2.h"
#include "../vector/USIVec2.h"


class Shape
{
public:
	Shape(const ShapeType& type) : type(type) {}

	inline void setType(const ShapeType& t) { type = t; }
	inline const ShapeType& getType() { return type; }
	
	virtual const GLboolean isInside(const GLfloat& x, const GLfloat& y) { return false; }
	virtual const GLboolean isInside(const FVec2& value) { return false; }
	virtual const GLboolean isInside(const USIVec2& value) { return false; }

protected:
	ShapeType type;
};