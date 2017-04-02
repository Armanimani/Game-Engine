#pragma once

#include "../util/shape/RectangleShape.h"
#include "../camera/Camera.h"


class Viewport
{
public:
	
	Viewport(std::shared_ptr<RectangleShape> rect, std::shared_ptr<Camera> cam) : rect(rect), cam(cam) {}

	inline void prepare()
	{
		setGLViewport();
	}

	inline void setCamera(const std::shared_ptr<Camera> camera) { cam = camera; }
	inline const std::shared_ptr<Camera> getCamera() {return cam; }

	inline void setRectangle(const std::shared_ptr<RectangleShape> value) { rect = value; }
	inline const std::shared_ptr<RectangleShape> getRect() { return rect; }
	
	inline void setGLViewport() { glViewport(rect->getXMin(), rect->getYMin(), rect->getWidth(), rect->getHeight()); }
	inline const GLfloat& getAspectRatio() {return rect->getAspectRatio(); }

protected:
	std::shared_ptr<Camera> cam;
	std::shared_ptr<RectangleShape> rect;
};