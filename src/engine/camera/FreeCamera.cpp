#include "FreeCamera.h"

void FreeCamera::rotateRight(const GLfloat & value)
{
	glm::mat4 rotationMat = glm::rotate(glm::radians(10 * value), right);
	direction = glm::vec3(rotationMat * glm::vec4(direction, 1.0f));
	up = glm::vec3(rotationMat * glm::vec4(up, 1.0f));
}

void FreeCamera::rotateUp(const GLfloat & value)
{
	glm::mat4 rotationMat = glm::rotate(glm::radians(10 * value), up);
	direction = glm::vec3(rotationMat * glm::vec4(direction, 1.0f));
	right = glm::vec3(rotationMat * glm::vec4(right, 1.0f));
}

void FreeCamera::orbit(const glm::vec2 & value)
{
	rotateUp(value.x);
	rotateRight(value.y);
}

void FreeCamera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
}
