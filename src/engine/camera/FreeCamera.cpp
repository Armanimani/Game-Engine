#include "FreeCamera.h"

void FreeCamera::rotateForward(const GLfloat & value)
{
	glm::mat4 rotationMat = glm::rotate(glm::radians(value), direction);
	up = glm::vec3(rotationMat * glm::vec4(up, 1.0f));
	up = glm::normalize(up);
	right = glm::vec3(rotationMat * glm::vec4(right, 1.0f));
	right = glm::normalize(right);
}

void FreeCamera::rotateRight(const GLfloat & value)
{
	glm::mat4 rotationMat = glm::rotate(glm::radians(value), right);
	direction = glm::vec3(rotationMat * glm::vec4(direction, 1.0f));
	direction = glm::normalize(direction);
	up = glm::vec3(rotationMat * glm::vec4(up, 1.0f));
	up = glm::normalize(up);
}

void FreeCamera::rotateUp(const GLfloat & value)
{
	glm::mat4 rotationMat = glm::rotate(glm::radians(value), up);
	direction = glm::vec3(rotationMat * glm::vec4(direction, 1.0f));
	direction = glm::normalize(direction);
	right = glm::vec3(rotationMat * glm::vec4(right, 1.0f));
	right = glm::normalize(right);
}

void FreeCamera::orbit(const glm::vec2 & value)
{
	rotateUp(value.x);
	rotateRight(value.y);
}