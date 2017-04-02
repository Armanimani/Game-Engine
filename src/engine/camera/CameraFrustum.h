#pragma once
#include <glew\GL\glew.h>
#include <memory>

struct CameraFrustum
{
	GLfloat FOV = 60.0f;
	GLfloat nearPlane = 0.5f;
	GLfloat farPlane = 10.0f;

	GLfloat viewLeft = -1.0f;
	GLfloat viewRight = 1.0f;
	GLfloat viewTop = -1.0f;
	GLfloat viewBottom = 1.0f;
	GLfloat viewFront = 1.0f;
	GLfloat viewBack = -1.0f;

	std::shared_ptr<unsigned short int> viewportWidth; // not reliable ! aspect ratio added!
	std::shared_ptr<unsigned short int> viewportHeight; // not reliable!

	GLfloat aspectRatio;
};