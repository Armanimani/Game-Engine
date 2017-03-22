#include "TargetCamera.h"
#include <iostream>

const GLfloat TOLERANCE = 1.0;

void TargetCamera::moveForward(const GLfloat & value)
{
	std::cout << position.x << " " << position.y << " " << position.z << "    " << target.x << " " << target.y << " " << target.z << std::endl;
	position += direction * value;
	target += direction * value;
}

void TargetCamera::moveRight(const GLfloat & value)
{
	position += right * value;
	target += right * value;
}

void TargetCamera::moveUp(const GLfloat & value)
{
	position += up * value;
	target += up * value;
}

void TargetCamera::rotateForward(const GLfloat & value)
{
	FreeCamera::rotateForward(value);
}

void TargetCamera::rotateRight(const GLfloat & value)
{
	GLfloat distance = glm::length(target - position);
	position = target;
	FreeCamera::rotateRight(value);
	position = target + direction * (-distance);
}

void TargetCamera::rotateUp(const GLfloat & value)
{
	GLfloat distance = glm::length(target - position);
	position = target;
	FreeCamera::rotateUp(value);
	position = target + direction * (-distance);
}

void TargetCamera::orbit(const glm::vec2 & value)
{
	rotateUp(value.x);
	rotateRight(value.y);
}

void TargetCamera::zoom(const GLfloat & value)
{
	GLfloat maxDistance =  glm::length(target - position) - TOLERANCE;
	GLfloat v;
	if (value > maxDistance) v = maxDistance;
	else v = value;

	position += direction * v;
}
