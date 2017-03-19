#include "FreeCamera.h"

void FreeCamera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
}
