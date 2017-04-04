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
	
	virtual const GLboolean isInside(const GLuint& x, const GLuint& y) { return false; }

protected:
	ShapeType type;
};