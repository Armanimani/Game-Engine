#pragma once
#include <glew\GL\glew.h>
#include <memory>

struct CameraFrustum
{
	GLfloat FOV = 60.0f;
	GLfloat nearPlane = 0.5f;
	GLfloat farPlane = 10.0f;

	std::shared_ptr<unsigned short int> viewportWidth;
	std::shared_ptr<unsigned short int> viewportHeight;
};